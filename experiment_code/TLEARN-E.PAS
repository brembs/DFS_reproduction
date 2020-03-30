(*
ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
บ                        Messprogramm fr                            บ
บ                     T - Lern - Experiment                          บ
บ                                                                    บ
บ               (c) 26.Feb.1993, R.W.  Version 1.1                   บ
บ                          tlern-a.pas                               บ
บ                  Einzel- oder Dreifachmessungen                    บ
บ                                                                    บ
บ               (c) 03.Sep.1994, R.W.  Version 2.0 (engl.)           บ
บ                    tlearn-b.pas to tlearn-d.pas                    บ
บ                 for single- to quintuple-recordings                บ
บ                                                                    บ
บ               (c) 16.Oct.1994, R.W.  Version 3.0 (engl.)           บ
บ                         with replay-option                         บ
บ                                                                    บ
บ               (c) 22.Oct.1994, R.W.  Version 3.1 (engl.)           บ
บ                         with replay-option                         บ
บ last edition: 2088 lines, 62069 bytes, 1:46 pm, marked 'READ ONLY' บ
ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
--------------------for flightsimulator in Beijing------------------------
              f=20Hz sampling rate in combination with Multilab
*)

program TlearnExp;

uses dos,crt,graph,hcopyVGA,{NecP6,}timedate,world,messrout,LasrHPGL;

type  str4      =     string[4];
      str6      =     string[6];
      str8      =     string[8];
      str10     =     string[10];
      inf       =     record
       HeatedPattern  : char;
       fly            : string[20];
       date,DayTime   : string[40];
       remarks        : string[80];
       ExpType        : array[1..15] of str4;
       duration      : array[1..15] of integer;
       NofRecs,NofData,NofFiles: integer;
      end;
      dta       =     record
       trq,psi        : array[0.. 1200] of integer;
      end;

var
    ExpType                             : array[1..15] of str4;
    duration                            : array[1..15] of integer;
    la                                  : array[1..15] of str6;
    ReplayFile                          : array[1.. 5] of str8;
    file_name,ReplFileName,PathToData   : string[50];
    DayTime,t1,t2                       : string[40];
    s,u,loop,ExpDisp                    : str10;
    tr,te,rp,heat,shut,name,name_,nov   : str8;
    torque,pos                          : array[0..12000] of integer;
    histo                               : array[-125..125, 1..3] of word;
    ok,color                            : word;
    data                                : dta;
    infoData                            : inf;
    InfoFile                            : file of inf;
    DataFile                            : file of dta;
    i,k,n,x,Nr,NofPeriods,TotalTime,NofData,zeile,
    fileNr,line,RecNr,NofRecs,len,cursor,
    code,psi,trq,Sector,OldSector,n_,
    StepInto,freq,NofData_,GraphDriver,
    GraphMode,bias,dir,nZeil,NofFiles,
    Fnr,X_,Y_,Toffs,indToffs,NofPauses,
    fp,rfp,snd                          : integer;
    col                                 : byte;
    psi_,trq_,y,y0,y1,y2,t,ts,tl,lambda,
    Bbr,k_,y11,y22,Y1old,y2old,t0,
    y11old,y22old,Xo,Yo,sum             : real;
    b,c,bu,HeatedPattern,ch,patt        : char;
    quit,StorageFlag,break,ClosedLoop,
    AutoDetect                          : boolean;
    MenueItems                          : set of char;


const   ESC      : char = chr(27);
        normal   : integer = 1;
        inverted : integer = -1;
        hot      : integer = 1;
        cold     : integer = -1;
{-------------------------------------------------}
procedure abort;
begin
 c:=ReadKey;
 if c=chr(27) then begin
  break:=true;
 end;
end;
{-------------------------------------------------}
procedure EnterName;
var ASCII : integer;
    ch : char;
begin
  repeat
   GotoXY(15,Zeile);write('        ');
   GotoXY(15,Zeile);write(name);
   ch := readkey;
   ASCII := ord(ch);
   case ASCII of
    8 : delete(name,length(name),1);
    13: EXIT;
    else  name := name+ch;
   end;
  until ASCII = 13;
end;
{*---------------------------------------------------------*}
procedure EnterFileName;
begin
 ClrScr;
 GotoXY(10, 8);writeln('the previous filename was: ',name);
 GotoXY(10,10);
 writeln('please type actual filename (without path and .ext) :');
 Zeile := 12;
 EnterName;
 if StorageFlag then begin
  GotoXY(10,14);write('fly     : '); readln(InfoData.fly);
  GotoXY(10,15);write('remarks : ');
  GotoXY(1,16);ClrEol;readln(InfoData.remarks);
 end;
end;
{*--------------------------------------------------------------------*}
procedure ExistTest;
begin
     break := false;
        if (IOresult = ok) then begin
          Lampe_aus;
          CloseShutter;
          ClrScr;
          GotoXY(10,12);write('This file exists already !');
          GotoXY(10,14);write('< O >  Overwrite');
          GotoXY(10,16);write('< C >  Change filename & save');
          GotoXY(10,18);write('       Don`t save and ...');
          GotoXY(10,19);write('< Q >  ...quit experiment     < ESC >  ...continue experiment');
          repeat bu:=ReadKey until UpCase(bu) in['O','C','Q',ESC];
          case UpCase(bu) of
          'C' : begin
                 close(InfoFile);
                 StorageFlag := false;
                 EnterFileName;
                 file_name := PathToData + name + '.inf';
                 Assign(InfoFile,file_name);
                 {$I-} Reset(InfoFile); {$I+}
                 ExistTest;
                end;
           #$1B,'Q' : begin
                       close(InfoFile);
                       break := true;
                       EXIT;
                      end;
           end;
          end; { if IOresult .. }
end;
{*--------------------------------------------------------------------*}
procedure StoreInfoFile(nam:str8);
begin
      file_name:=PathToData+nam+'.inf';
      Assign(InfoFile,file_name);
      {$I-}  Reset(InfoFile);  {$I+}
      ExistTest;
      if break then EXIT;
      Rewrite(InfoFile);
      write(InfoFile,InfoData);
      close(InfoFile);
end;
{*---------------------------------------------------------*}
procedure StoreDataFile(nam:str8);
begin
     file_name:=PathToData+nam+'.dta';
     Assign(DataFile,file_name);
     Rewrite(DataFile);
     for RecNr := 1 to NofRecs do begin
      n := (RecNr-1)*1200;
      for i := 1 to 1200 do begin
       data.trq[i]  :=  torque[i+n];
       data.psi[i]  :=  pos[i+n];
      end;
      write(DataFile,data);
     end;
     close(DataFile);
end;
{*---------------------------------------------------------*}
Procedure SaveData(auto : boolean);
begin
 ClrScr;
 bu := 'X';
 if not auto then begin
     GotoXY(15,15);writeln('Save data ?   < Y / N >');
     repeat bu := ReadKey until UpCase(bu) in ['Y','N'];
 end;
   if UpCase(bu) = 'N' then EXIT;
      StorageFlag := true;
      if not auto then begin
       GotoXY(1,15);ClrEol;
       EnterFileName;
      end else begin
       s := chr(96+Fnr);
       len := length(name);
       if len<8 then cursor := len+1 else cursor := len;
       delete(name,len+1,8-len);
       Name := Name + s;
      end;
      StorageFlag := false;
      GotoXY(15,16);write('data are stored in : ');
      file_name :=PathToData+name+'.dta';
      writeln(file_name);
      NofRecs   := NofData div 1200;
      if (NofData mod 1200) > 0  then   NofRecs := NofRecs + 1;
      InfoData.HeatedPattern       := HeatedPattern;
      InfoData.NofRecs             := NofRecs;
      InfoData.NofData             := NofData;
      InfoData.NofFiles            := NofFiles;
      i := Nr;
      for Nr:=1 to 15 do begin
       InfoData.ExpType[Nr]   := ExpType[Nr];
       InfoData.duration[Nr]  := duration[Nr];
      end;
      Nr := i;
      StoreInfoFile(name);
      if break then EXIT;
      StoreDataFile(name);
      if break then EXIT;

end;
{--------------------------------------------------}
procedure DebugPosTrace;
var    psi:real;

begin
 i := 0;
 repeat
  inc(i);                                
  if abs(pos[i])>2000 then begin
   psi := pos[i];
   dec(i);
   repeat
    inc(i);
    psi := psi-(torque[i]+t0)*80*k_/180/freq;        {  freq=1/dt  }
    if psi>2048  then psi := psi-4096;
    if psi<-2048 then psi := psi+4096;
    pos[i] := trunc(psi);
   until (abs(pos[i])<2000) or (i>=NofData);
  end;
 until i>=NofData;
end;
{*---------------------------------------------------------*}
Procedure ReadFile;
begin
  TextBackground(blue);
  ClrScr;
  TextColor(white);

   StorageFlag := false;
   EnterFileName;
   file_name:=PathToData+name+'.inf';
	 GotoXY(10,10);ClrEol;write('data are read from :');
	 write(file_name);
         Assign(InfoFile,file_name);
 {$I-}   Reset(InfoFile); {$I+}
     if (IOresult<>ok) then begin
      GotoXY(10,16);ClrEol;
      write('Unknown file : ',file_name);
      repeat until KeyPressed;
      EXIT;
     end;
     Read(InfoFile,InfoData);
     close(InfoFile);
     HeatedPattern       := InfoData.HeatedPattern;
     NofRecs             := InfoData.NofRecs;
     NofData             := InfoData.NofData;
     NofFiles            := InfoData.NofFiles;
     for Nr:=1 to 15 do begin
      ExpType[Nr]   := InfoData.ExpType[Nr];
      duration[Nr] := InfoData.duration[Nr];
     end;

     Nr := 0;
     repeat inc(Nr,1) until (ExpType[Nr]='    ') or (Nr=15);
     NofPeriods := Nr;
     if (ExpType[Nr]='    ') then dec(NofPeriods);
   file_name:=PathToData+name+'.dta';
	 GotoXY(10,10); write('data are read from : ');
	 write(file_name);
         Assign(DataFile,file_name);
 {$I-}   Reset(DataFile); {$I+}
     if (IOresult<>ok) then begin
      GotoXY(10,16);write('unknown file : ',file_name);
      repeat until KeyPressed;
      EXIT;
     end;
     for RecNr := 1 to NofRecs do begin
      Read(DataFile,Data);
      n := (RecNr-1)*1200;
      for i:=1 to 1200 do begin
       torque[i+n] := data.trq[i];
       pos[i+n]    := data.psi[i];
      end;
     end;
     close(DataFile);
     DebugPosTrace;
end;
{---------------------------------------------------------}
procedure LoadReplayFile(FileNo : integer);
begin

   ReplFileName:=PathToData+ReplayFile[Fnr]+'.dta';
         Assign(DataFile,ReplFileName);
 {$I-}   Reset(DataFile); {$I+}
     if (IOresult<>ok) then begin
      GotoXY(10,16);write('unknown ReplayFile : ',ReplFileName);
      repeat until KeyPressed;
      EXIT;
     end;
     for RecNr := 1 to NofRecs do begin
      Read(DataFile,Data);
      n := (RecNr-1)*1200;
      for i:=1 to 1200 do begin
       torque[i+n] := data.trq[i];
       pos[i+n]    := data.psi[i];
      end;
     end;
     close(DataFile);
     DebugPosTrace;
end;
{---------------------------------------------------------}
procedure OpenDialogBox(x1,y1,x2,y2 : integer; colour : ShortInt);
begin
  StoreWorld(3,X1,Y1,X2,Y2);
  if WorldError then exit;
  SetFillStyle(SolidFill,colour);
  barW(x1,y1,x2,y2);
  rectangleW(x1,y1,x2,y2);
end;
{-------------------------------------------------------}
procedure CloseDialogBox(x1,y1 : integer);
begin
  RestoreWorld(3,X1,Y1,NormalPut);
  FreeWorldMem(3);
end;
{---------------------------------------------------------}
procedure LabelArenaSpeed;
begin
  SetFillStyle(SolidFill,yellow);
  barW(195,-111,235,-118);
  SetTextJustify(CenterText,CenterText);
  SetColor(black);
  str(-bias:4,s);
  OutTextXYW(205,-115,s);
  SetColor(yellow);
end;
{---------------------------------------------------------}
procedure IndicateTorqueOffset(color :word );
begin
  SetColor(color);
  LineW(X_+1,Y_-indToffs,X_+5,Y_-indToffs);
  SetColor(yellow);
end;
{---------------------------------------------------------}
procedure SwitchOpenClosed;
begin
 if ClosedLoop then begin
  ClosedLoop_off(1);
  ClosedLoop := false;
  loop := 'open loop';
 end else begin
  ClosedLoop := true;
  ClosedLoop_on(1);
  loop := 'cl. loop'
 end;
  SetFillStyle(SolidFill,yellow);
  barW(25,-111,95,-118);
  SetTextJustify(CenterText,CenterText);
  SetColor(black);
  OutTextXYW(60,-115,loop);
  SetColor(yellow);
end;
{---------------------------------------------------------}
procedure SetArenaNull;
var  dPsi : integer;
begin
  if ClosedLoop then SwitchOpenClosed;
  ArenaSpeed_on(1);
  repeat
   dPsi :=  ArenaPos(1);
   if dPsi>1000 then dPsi := 1000;
   if dPsi<-1000 then dPsi := -1000;
   SetArenaSpeed(1,2047 + dPsi);
  until dPsi=0;
  SetArenaSpeed(1,2047);
  ArenaSpeed_off(1);
end;
{------------------------------------------------}
procedure ChangePatterns;
begin
   ClosedLoop := false;
   ClosedLoop_off(1);
   SetArenaNull;
       sound(200);delay(500);NoSound;
       delay(150);
       sound(200);delay(500);NoSound;
       delay(150);
       sound(200);delay(500);NoSound;
       delay(150);
       sound(50);delay(2400);NoSound;
         OpenDialogBox(180,20,320,0,red);
         OutTextXYW(250,15,'Change Patterns');
         OutTextXYW(250, 5,'CONT -> AnyKey');
         repeat until KeyPressed;
         bu := ReadKey;
         CloseDialogBox(180,20);
   ClosedLoop := true;
   ClosedLoop_on(1);
end;
{------------------------------------------------}
procedure interrupt(Inr : integer);
begin
 c:=ReadKey;
 case UpCase(c) of
  chr(27) : break:=true;
  #16 : begin     { CTRL-P }
         sound(1000); delay(100); NoSound;
         OpenDialogBox(180,20,320,0,red);
         OutTextXYW(250,15,'program paused');
         OutTextXYW(250, 5,'CONT -> AnyKey');
         repeat until KeyPressed;
         bu := ReadKey;
         CloseDialogBox(180,20);
        end;
  'L' : SwitchOpenClosed;
  'N',#72 : SetArenaNull;
  '+' : begin
         ArenaSpeed_on(1);
         bias := bias - 50;
         SetArenaSpeed(1,2047+bias);
         LabelArenaSpeed;
        end;
  '0',#80 : begin
         bias := 0;
         SetArenaSpeed(1,2047);
         ArenaSpeed_off(1);
         LabelArenaSpeed;
        end;
  '-' : begin
         ArenaSpeed_on(1);
         bias := bias + 50;
         SetArenaSpeed(1,2047+bias);
         LabelArenaSpeed;
        end;
  #75 : begin
         ArenaSpeed_on(1);
         bias := bias + 200;
         SetArenaSpeed(1,2047+bias);
         LabelArenaSpeed;
        end;
  #77 : begin
         ArenaSpeed_on(1);
         bias := bias - 200;
         SetArenaSpeed(1,2047+bias);
         LabelArenaSpeed;
        end;
  #73 : begin                { PageUp }
         IndicateTorqueOffset(blue);
         Toffs := Toffs - 11;
         indToffs := indToffs-1;
         IndicateTorqueOffset(LightRed);
         SetTorqueOffset(2048-Toffs);
        end;
  #81 : begin                { PageDown }
         IndicateTorqueOffset(blue);
         Toffs := Toffs + 11;
         indToffs := indToffs + 1;
         SetTorqueOffset(2048-Toffs);
         IndicateTorqueOffset(LightRed);
        end;
  #32 : BlowFly; {space blst die Fliege an}
  'A' : if (AutoDetect=true) then begin
  					AutoDetect:=false;
  					color := GetColor;
            SetColor(blue);
            SetTextJustify(CenterText,LeftText);
            bar(450,470,650,500);
            OutTextXY(543,480,'AutoDetect=Off');
            SetColor(color);
  					end else begin
  					 AutoDetect:=true;
  					 color := GetColor;
             SetColor(blue);
             SetTextJustify(CenterText,LeftText);
             bar(450,470,650,500);
             OutTextXY(543,480,'AutoDetect=On');
             SetColor(color);
  					end;
  end;
end;
{---------------------------------------------------------}
procedure EnterGraphics;
var     ErrCode : integer;
const   path    = 'c:\tp\bgi';

begin
 GraphDriver := detect;
 InitGraph(GraphDriver,GraphMode,path);
 ErrCode := GraphResult;
 if ErrCode <> grOk then begin
   writeln('GraphicsError ',ErrCode,' : ',GraphErrorMsg(ErrCode));
   repeat until KeyPressed;
   CloseGraph;
   break := true;
 end;
 SetBkColor(blue);
 SetColor(yellow);
end;
{*----------------------------------------------------------*}
procedure DrawTpatterns;
begin

 for n:=1 to 3 do begin
  Xo := 400 - (n mod 2)*300;
  Yo := 10 - (n div 3)*100;
  LineW(Xo-125,Yo,Xo+125,Yo);
  SetLineStyle(DottedLn,0,NormWidth);
  LineW(Xo-125/180*135,Yo,Xo-125/180*135,Yo+85);
  LineW(Xo-125/180* 45,Yo,Xo-125/180* 45,Yo+85);
  LineW(Xo+125/180* 45,Yo,Xo+125/180* 45,Yo+85);
  LineW(Xo+125/180*135,Yo,Xo+125/180*135,Yo+85);
  SetLineStyle(SolidLn,0,NormWidth);
  if HeatedPattern='ย' then SetFillStyle(SolidFill,LightGreen) else SetFillStyle(SolidFill,yellow);
  BarW(Xo-3,Yo+85,Xo+3,Yo+78);
  BarW(Xo-10,Yo+85,Xo+10,Yo+82.5);
  BarW(Xo-125,Yo+85,Xo-122,Yo+78);
  BarW(Xo-125,Yo+85,Xo-115,Yo+82.5);
  BarW(Xo+122,Yo+85,Xo+125,Yo+78);
  BarW(Xo+115,Yo+85,Xo+125,Yo+82.5);
  if HeatedPattern='ย' then SetFillStyle(SolidFill,Yellow) else SetFillStyle(SolidFill,LightGreen);
  BarW(Xo-65.5,Yo+85,Xo-59.5,Yo+78);
  BarW(Xo-72.5,Yo+80.5,Xo-52.5,Yo+78);
  BarW(Xo+59.5,Yo+85,Xo+65.5,Yo+78);
  BarW(Xo+52.5,Yo+80.5,Xo+72.5,Yo+78);
  SetColor(yellow);
 end;
end;
{*----------------------------------------------------------*}
procedure HistoFrame;
begin
  break := false;
  EnterGraphics;
  if break then EXIT;
  SetViewPort(0,0,GetMaxX,GetMaxY,true);
  DefineWorld(-50,-120,550,100);
  rectangleW(-50,100,550,-100);
{  SetLineStyle(SolidLn,0,ThickWidth);  }
  LineW(-50,0,550,0);
  LineW(250,-100,250,100);
  SetLineStyle(SolidLn,0,NormWidth);
  DrawTpatterns;
  lineW(-50,-105,-50,-120);
  SetTextJustify(CenterText,CenterText);
  name_ := copy(name,1,7);
  for n:=1 to NofFiles do begin
   lineW(-50+120*n,-105,-50+120*n,-120);
   lineW(-50+120*n-120,-105,-50+120*n,-105);
   lineW(-50+120*n-120,-111,-50+120*n,-111);
   lineW(-50+120*n-120,-120,-50+120*n,-120);
   s := chr(96+n);
   OutTextXYW(-50+120*n-60,-108,name_+s);
  end;
  SetTextJustify(RightText,CenterText);
  for N:=1 to NofPeriods do OutTextXYW(-55+N*40,-116,ExpType[N]);
end;
{*----------------------------------------------------------*}
procedure TimeTraceWindow;
begin
   SetColor(blue);
   lineW(250,-100,250,0);
   SetColor(yellow);
   SetLineStyle(SolidLn,0,ThickWidth);
   RectangleW(248,0,550,-100);
   SetLineStyle(DottedLn,0,NormWidth);
   Yo := 12.5;
   X_ := 250;       {for TorqueOffsetMarker}
   Y_ := -50;
   repeat
    Yo := Yo - 25;
    LineW(248,Yo,550,Yo);
   until Yo<=-87.5;
   SetLineStyle(DashedLn,0,NormWidth);
   LineW(248,-50,550,-50);
end;
{*----------------------------------------------------------*}
procedure frame(OsciMode : boolean);
begin
 break := false;
 EnterGraphics;
 if break then EXIT;
 SetViewPort(0,0,GetMaxX,GetMaxY,true);
  DefineWorld(-50,-120,550,100);
 rectangleW(0,100,500,0);
 rectangleW(0,0,500,-100);
 SetLineStyle(SolidLn,0,ThickWidth);
 LineW(0,0,500,0);
   SetLineStyle(DottedLn,0,NormWidth);
   Yo := -112.5;
   repeat
    Yo := Yo + 25;
    LineW(0,Yo,500,Yo);
   until Yo>=87.5;
   SetLineStyle(DashedLn,0,NormWidth);
   LineW(0,-50,500,-50);
   LineW(0, 50,500, 50);
   SetLineStyle(SolidLn,0,NormWidth);
 SetTextStyle(SmallFont,VertDir,6);
 SetTextJustify(CenterText,CenterText);
 OutTextXYW(-45,0,'yaw torque T(t) [mdyncm] ---->');
 SetTextStyle(DefaultFont,HorizDir,1);
  SetTextJustify(RightText,CenterText);
  y:=100;
  i:=50;
  repeat
   y:=y-10;
   i:=i-10;
   lineW(0,y,5,y);
   str(i:3,s);
   if (i mod 20)=0 then OutTextXYW(-5,y,s);
   if y=0 then i := 50;
  until y=-100;
 SetTextJustify(LeftText,CenterText);
 OutTextXYW(505,97,' 180');
 y:=100;
 t:=180;
 repeat
  y:=y-25;
  t:=t-90;
  lineW(495,y,500,y);
  str(t:4:0,s);
  OutTextXYW(505,y,s);
  if y=0 then t:=180;
 until y=-100;

 if OsciMode then begin
  SetTextJustify(CenterText,CenterText);
  OutTextXYW(0,-105,'0');
  x:=0;
  t:=0;
  SetLineStyle(SolidLn,0,ThickWidth);
  repeat
   t:=t+5;
   x:=x+trunc(500/6+0.5);
   lineW(x,-100,x,-98);
   lineW(x,0,x,2);
   str(t:4:1,s);
   OutTextxyW(x-5,-105,s);
  until x>490;
  SetLineStyle(SolidLn,0,NormWidth);
  OutTextXYW(480,-115,'t [s] ---->');

  SetTextJustify(RightText,CenterText);
  OutTextXYW( 20,-115,'L ->');
  OutTextXYW(200,-115,'bias : ');
  OutTextXYW(380,-115,'N -> ArenaNull');
  SetFillStyle(SolidFill,yellow);
  barW(25,-111,95,-118);
  barW(195,-111,235,-118);
  SetTextJustify(CenterText,CenterText);
  SetColor(black);
  OutTextXYW(60,-115,loop);
  str(-bias:4,s);
  OutTextXYW(205,-115,s);
  SetColor(yellow);
 end else begin
  lineW(-50,-105,-50,-120);
  SetTextJustify(CenterText,CenterText);
  name_ := copy(name,1,7);
  for n:=1 to NofFiles do begin
   lineW(-50+120*n,-105,-50+120*n,-120);
   lineW(-50+120*n-120,-105,-50+120*n,-105);
   lineW(-50+120*n-120,-111,-50+120*n,-111);
   lineW(-50+120*n-120,-120,-50+120*n,-120);
   s := chr(96+n);
   OutTextXYW(-50+120*n-60,-108,name_+s);
  end;
  SetTextJustify(RightText,CenterText);
  for N:=1 to NofPeriods do OutTextXYW(-55+N*40,-116,ExpType[N]);
 end;    { else if OsciMode }
   X_ := 0;       { for TorqueOffsetMarker }
   Y_ := 50;
 end;
{*--------------------------------------------------------------------*}
procedure OnLineGraph;
var y0,y1,y2         : real;
    i,x,n            : integer;
begin
 break := false;
 frame(true);
 SetTextStyle(DefaultFont,HorizDir,1);
 StoreWorld(1,0,100,500,0);
 if WorldError then exit;
 SetLineStyle(SolidLn,0,NormWidth);
 repeat
 for i:=1 to 2 do begin
  if i=1 then y0 := 50 else y0 := -50;
  y11 := YawTorque/2048*80 + y0;
  y22 := ArenaPos(1)/2048*50 + y0;
  for x:=1 to 500 do begin
   if KeyPressed then interrupt(1);
   if break then begin
    CloseGraph;
    FreeWorldMem(1);
    EXIT;
   end;
   y1 := 0;
   y2 := 0;
   for n := 1 to 100 do begin
    y1 := y1 + YawTorque;
    y2 := y2 + ArenaPos(1);
   end;
   y1 := y1/100/2048*80;
   y2 := y2/100/2048*50;
   if y1>50 then y1 := 50; if y1<-50 then y1 := -50;
   if y2>50 then y2 := 50; if y2<-50 then y2 := -50;
   y1 := y1 + Y0; y2 := y2 +Y0;
   lineW(x-1,y11,x,y1);
   if abs(y2-y22)<30 then lineW(x-1,y22,x,y2);
   y11 := y1;
   y22 := y2;
   delay(2);
  end;
 end;
 RestoreWorld(1,0,100,NormalPut);
 RestoreWorld(1,0,0,NormalPut);
 until break;
 FreeWorldMem(1);
 CloseGraph;
end;
{*--------------------------------------------------------------------*}
procedure TrqPos;
begin
 ClrScr;
 repeat
  writeln(YawTorque:8,ArenaPos(1));
 until KeyPressed;
end;
{*--------------------------------------------------------------------*}
procedure SetDefaultConditions;
 begin
  SetArenaSpeed(1,2048);
  ArenaSpeed_off(1);
  if not ClosedLoop then begin
   ClosedLoop_off(1);
   loop := 'open loop';
  end;
  lampe_aus;
  CloseShutter;
  heat := ' off';
  shut := ' closed';
  AutoDetect:=true;
  bias := 0;
  NofPauses := 0;
  Toffs := 0;
  indToffs := 0;
  SetTorqueOffset(2048-Toffs);
 end;
{-------------------------------------------------}
procedure FlyMonitor;
begin
  SetDefaultConditions;
{  TrqPos; }
  OnLineGraph;
  SetDefaultConditions;
end;
{*ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ*}
procedure TimeTraces;
var PsiOld,PsiNew : real;
begin
 break := false;
 EnterGraphics;
 if break then EXIT;
 SetViewPort(0,0,GetMaxX,GetMaxY,true);
 DefineWorld(-50,-15,520,385);
 SetTextJustify(RightText,CenterText);
 for k:=1 to 4 do begin
  y0 := (k-1)*100;
  SetLineStyle(SolidLn,0,NormWidth);
  SetFillStyle(WideDotFill,green);
  barW(0,y0+80,500,y0+70);
  barW(0,y0+50,500,y0+30);
  barW(0,y0+10,500,y0);
  rectangleW(0,y0+80,500,y0);
  y:=80;
  i:=180;
  repeat
   lineW(0,y+y0,3,y+y0);
   str(i:3,s);
   if (i mod 90)=0 then OutTextXYW(-5,y+y0,s);
   y:=y-10;
   i:=i-45;
  until y=-10;
  SetLineStyle(DottedLn,0,NormWidth);
  LineW(0,y0+40,500,Y0+40);
 end;
 SetLineStyle(SolidLn,0,NormWidth);
 SetTextStyle(SmallFont,VertDir,6);
 SetTextJustify(CenterText,CenterText);
 OutTextXYW(-45,190,'arena position psi(t) [๘]---->');
 SetTextStyle(DefaultFont,HorizDir,1);
 SetTextJustify(LeftText,BottomText);
 str(TotalTime,s);
 OutTextXYW(-50,-15,InfoData.fly+
            ' from '+InfoData.date+'   t(tot)= '+s+'s   '+file_name);
 SetTextStyle(SmallFont,HorizDir,5);
 OutTextXYW(10,287,'Heat with : '+HeatedPattern);
 SetTextStyle(DefaultFont,HorizDir,1);

 Nr := 1;
 nZeil := trunc(NofData/4);
 NofData_ := freq*duration[Nr];
 for i := 2 to NofData do begin
  if KeyPressed then begin
   abort;
   if break then EXIT;
  end;
  t  := (i mod nZeil)/nZeil * 500;
  y0 := 340-(i div nZeil)*100;
  if i=NofData_ then begin
   inc(Nr,1);
   NofData_ := NofData_ + freq*duration[Nr];
   SetLineStyle(DottedLn,0,NormWidth);
   lineW(t,Y0-40,t,y0+40);
   SetLineStyle(SolidLn,0,NormWidth);
  end;
  if abs(pos[i]-pos[i-1])<400 then
    lineW(t-1,y0+pos[i-1]/2048*40,t,y0+pos[i]/2048*40);
 end;

 Nr := 1;
 nZeil := trunc(NofData/4);
 NofData_ := freq*duration[Nr];
 SetColor(LightRed);
 for i := 2 to NofData do begin
  if KeyPressed then begin
   abort;
   if break then EXIT;
  end;
  t  := (i mod nZeil)/nZeil * 500;
  y0 := 340-(i div nZeil)*100;
  if i=NofData_ then begin
   inc(Nr,1);
   NofData_ := NofData_ + freq*duration[Nr];
   SetLineStyle(DottedLn,0,NormWidth);
   lineW(t,Y0-40,t,y0+40);
   SetLineStyle(SolidLn,0,NormWidth);
  end;
    lineW(t-1,y0+torque[i-1]/2048*80,t,y0+torque[i]/2048*80);
 end;

 {  ----------  position trace calculated from torque (integral) : --------
 Nr := 1;
 nZeil := trunc(NofData/4);
 NofData_ := freq*duration[Nr];
 SetColor(LightRed);
 PsiNew := Pos[1]/2048*180;
 PsiOld := PsiNew;
 for i := 2 to NofData do begin
  if KeyPressed then begin
   abort;
   if break then EXIT;
  end;
  t  := (i mod nZeil)/nZeil * 500;
  y0 := 340-(i div nZeil)*100;
  if i=NofData_ then begin
   inc(Nr,1);
   NofData_ := NofData_ + freq*duration[Nr];
   PsiNew := pos[i]/2048*180;
   PsiOld := PsiNew;
  end;
  PsiNew := PsiNew-(torque[i]+t0)/2048*80*k_/freq;
  if PsiNew> 180 then PsiNew := PsiNew-360;
  if PsiNew<-180 then PsiNew := PsiNew+360;
  if abs(PsiNew-PsiOld)<300 then
    lineW(t-1,y0+PsiOld/180*40,t,y0+PsiNew/180*40);
  PsiOld := PsiNew;
 end;
*****}
end;
{*ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ*}
procedure PositionHisto;

begin
  for Nr:=1 to 3 do begin
   for psi:= -125 to 125 do Histo[psi,Nr] := 0;
  end;
  HistoFrame;
  SetTextJustify(CenterText,CenterText);
  OutTextXYW(470,-25,'(heat with '+HeatedPattern+')');
  SetTextJustify(LeftText,CenterText);
  if HeatedPattern='ม' then s := 'ย' else s := 'ม';
  OutTextXYW(275,-8,'preference index for '+s+':');
  lineW(275,-11,445,-11);
  OutTextXYW(275,-60,infodata.fly);
  OutTextXYW(275,-68,infodata.remarks);
  OutTextXYW(275,-76,infodata.date);
  OutTextXYW(275,-82,infodata.daytime);
  OutTextXYW(275,-90,file_name);
  Nr := 1;
  Xo := 400 - (Nr mod 2)*300;
  Yo := 10 - (Nr div 3)*100;
  NofData_ := freq * duration[Nr];
  s := copy(name,length(name),1);
  if (s='A') or (s='a') then  n_ := 0;
  if (s='B') or (s='b') then  n_ := 3;
  if (s='C') or (s='c') then  n_ := 6;
  if (s='D') or (s='d') then  n_ := 9;
  if (s='E') or (s='e') then  n_ := 12;
  if ExpType[Nr+n_]=tr then SetColor(LightGreen);
  if ExpType[Nr+n_]=te then SetColor(yellow);
  SetLineStyle(SolidLn,0,ThickWidth);
  ts := 0;
  tl := 0;
  for i:=1 to NofData do begin
   if KeyPressed then begin
    abort;
    if break then EXIT;
   end;
   psi := pos[i];
   if (abs(psi)<512) or (abs(psi)>1536) then ts:=ts+1 else tl:=tl+1;
   psi := trunc(psi/2048*125);
   Y1 := Histo[Psi,Nr];
   Y2 := Y1+1;
   Histo[psi,Nr] := trunc(Y2);
   LineW(Xo+psi,Yo+0.7*Y1,Xo+Psi,Yo+0.7*Y2);
   if i=NofData_ then begin
    if HeatedPattern='ม' then lambda := (ts-tl)/(tl+ts)
                         else lambda := (tl-ts)/(tl+ts);
    tl  := 0;
    ts  := 0;
    str(lambda:5:3,s);
    if not (lambda<0) then s := ' '+s;
    str(Nr,u);
    SetTextJustify(LeftText,CenterText);
    OutTextXYW(275,-10*(1+Nr),u+':   '+s);
    SetTextJustify(CenterText,CenterText);
    OutTextXYW(Xo,Yo-5,ExpType[Nr+n_]);
    inc(Nr,1);
    Xo := 400 - (Nr mod 2)*300;
    Yo := 10 - (Nr div 3)*100;
    NofData_ := NofData_ + freq*duration[Nr];
    if ExpType[Nr+n_]=tr then SetColor(Lightgreen);
    if ExpType[Nr+n_]=te then SetColor(yellow);
  end;
 end;
 SetColor(yellow);
end;
{--------------------------------------------------------}
function DetectPattern(psi : integer) : char;
begin
 if (abs(psi)<512) or (abs(psi)>1526) then DetectPattern := 'ย'
                                      else DetectPattern := 'ม';
end;
{------------------------------------------------}
procedure PlotTimeTraces;
var x,x1,x2 : real;
    psi,PosOld,resol    : integer;

begin
    resol := 4;
    ClrScr;
    GotoXY(15,10);writeln('plot to HP LaserJet ...');
    PlotInit;
    assign(HPLJ4,'LPT1');
    rewrite(HPLJ4);
    write(HPLJ4,'DF;');                   { Default values }
    Plotformat(hoch);
    SelectPen(1);
    PlotMetricHardclips(25,15,172,260);
    PlotScale(0,172,0,1700);
    MovePenTo(56,1100);
    write(HPLJ4,'SD1,21,2,1,4,12,5,0,6,0,7,4148;'); { designate 12pt Univers }
    write(HPLJ4,'SS;');                             { Select second font }
    write(HPLJ4,'SI;');                             { default character size }
    PlotLabelAbs(0,rechts_mittig,name+'.dta,  Heat with '+HeatedPattern);
    MovePenTo(56,100);
    for Nr:=1 to NofPeriods do PlotLabelAbs(0,rechts_mittig,ExpType[Nr]+' ');

    write(HPLJ4,'FT',10,',',1,';');        { FillType }

  for Nr:=1 to 3 do begin
  case Nr of
   1: Xo := 25;  
   2: Xo := 85;  
   3: Xo := 145;  
  end;
  writeln(HPLJ4,'PW',0.3:6:4,';');      { LineWidth }
  MovePenTo(Xo-25,0);PenDown;
  PlotTo(Xo-25,1700);PlotTo(Xo+25,1700);PlotTo(Xo+25,0);PlotTo(Xo-25,0);
  y := 0;
  repeat
   y := y + 1699/6;
   PlotLine(Xo+23.5,y,Xo+25,y);
  until y>=1700;
  writeln(HPLJ4,'PW',0.1:6:4,';');      { LineWidth }
  PlotLine(Xo-18.75,0,Xo-18.75,1700);
  PlotLine(Xo- 6.25,0,Xo- 6.25,1700);
  PlotLine(Xo+18.75,0,Xo+18.75,1700);
  PlotLine(Xo+ 6.25,0,Xo+ 6.25,1700);
  PlotLine(Xo,0,Xo,1700);

  If HeatedPattern='ม' then begin
   for k:=1 to 2 do  begin
    case k of
    1: begin
        x1 := Xo-18.75; x2 := Xo-6.25;
       end;
    2: begin
        x1 := Xo+6.25; x2 := Xo+18.75;
       end;
    end;  { case }
    MovePenTo(x1,0);
    write(HPLJ4,'RA',x2:5:4,',',1700.0:9:4,';');      { FillRectangleAbs }
   end;   { for k }
  end else begin
   for k:=1 to 3 do  begin
    case k of
    1: begin
        x1 := Xo-25; x2 := Xo-18.75;
       end;
    2: begin
        x1 := Xo-6.25; x2 := Xo+6.25;
       end;
    3: begin
        x1 := Xo+18.75; x2 := Xo+25;
       end;
    end;  { case }
    MovePenTo(x1,0);
    write(HPLJ4,'RA',x2:5:4,',',1700.0:9:4,';');      { FillRectangleAbs }
   end;   { for k }
  end;    { if HeatedPattern }
  k := (Nr-1)*freq*duration[Nr];
  NofData_ := freq*duration[Nr];

  writeln(HPLJ4,'PW',0.3:6:4,';');      { LineWidth }
  PosOld := pos[k+1];
  movePenTo(Xo-PosOld/2048*25,0);
  i := 0;
  repeat
  inc(i,resol);
   x := i/NofData_*1700;
   inc(k,resol);
   psi := pos[k];
   if abs(psi-PosOld)>2000 then begin
    if posOld<0 then PlotTo(Xo+25,x);
    if posOld>0 then PlotTo(Xo-25,x);
    MovePenTo(Xo-psi/2048*25,x);
   end;
   PlotTo(Xo-psi/2048*25,x);
   PosOld := psi;
  until i>=(NofData_-resol);

  writeln(HPLJ4,'PW',0.1:6:4,';');      { LineWidth }
  k := (Nr-1)*freq*duration[Nr];
  movePenTo(Xo-(torque[k+1]+16)/2048*50,0);

  i := 0;
  repeat
  inc(i,resol);
   x := i/NofData_*1700;
   inc(k,resol);
   PlotTo(Xo-(torque[k]+16)/2048*50,x);
  until i>=(NofData_-resol);

  k := (Nr-1)*freq*duration[Nr];
  i := 0;
  repeat
   inc(i,resol);
   x := i/NofData_*1700;
   inc(k,resol);
   psi  := pos[k];
   Patt := DetectPattern(psi);
   if Patt=HeatedPattern then PlotLine(Xo+25,x,Xo+26,x);
  until (i>=(NofData_-resol));

 end;

 PenUp;
 write(HPLJ4,chr(27)+'E');
 close(HPLJ4);
end;
{-----------------------------------------------}
procedure PlotHisto;
var s1 : char;
    n_ : integer;
begin
 break := false;
 EnterGraphics;
 if break then EXIT;
 SetViewPort(0,0,GetMaxX,GetMaxY,true);
 DefineWorld(-55,-2.5,620,1.1);
 SetTextStyle(DefaultFont,HorizDir,1);
 SetTextJustify(RightText,CenterText);
 lineW(0,0,600,0);
 lineW(-5,-1,-5,1);
 y := 1;
 i := 10;
 repeat
  lineW(-5,y,-3,y);
  str(i/10:0:1,s);
  if abs(i)<10 then begin
   str(abs(i),s);
   if i<0 then s := '-.' + s else s := '.' + s;
  end;
  if i=0 then s := '0';
  if (i mod 2)=0 then OutTextXYW(-10,y,s);
  y := y - 0.1;
  i := i - 1;
 until y < -1.1;
 SetTextJustify(CenterText,CenterText);
 lineW(0,-1.1,600,-1.1);
 x := 0;
 OutTextXYW(0,-1.2,'0');
 repeat
  lineW(x,-1.1,x,-1.08);
  x := x + 60;
  i := x div 60;
  str(i,s);
  if (i mod 2)=0 then OutTextXYW(x,-1.2,s);
 until x > 600;
 OutTextXYW(550,-1.3,'t[min] ---->');
 SetTextJustify(LeftText,CenterText);
 SetTextStyle(SmallFont,VertDir,5);
 OutTextXYW(-55,0,'lambda [rel.units] --->');
 SetTextStyle(DefaultFont,HorizDir,1);
 SetFillStyle(SolidFill,yellow);
 barW(25,0.9,35,0.7);
 barW(25,-0.9,35,-0.7);
 if HeatedPattern = 'ย' then begin
  barW(10,0.77,50,0.7);
  barW(10,-0.7,50,-0.77);
 end else begin
  barW(10,0.9,50,0.83);
  barW(10,-0.83,50,-0.9);
 end;
 SetTextJustify(CenterText,CenterText);
 OutTextXYW(30,0.97,'cold');
 OutTextXYW(30,-0.97,'hot');
 SetFillStyle(CloseDotFill,yellow);
 barW(360,-1.5,390,-1.7);
 rectangleW(360,-1.5,390,-1.7);
 SetFillStyle(LtSlashFill,yellow);
 barW(360,-1.8,390,-2);
 rectangleW(360,-1.8,390,-2);
 SetTextJustify(LeftText,BottomText);
 SetTextStyle(SmallFont,HorizDir,6);
 OutTextXYW(395,-1.7,'training');
 OutTextXYW(395,-2,'test');
 OutTextXYW(0,-1.5,infoData.fly);
 OutTextXYW(0,-1.65,'from '+infoData.date);
 OutTextXYW(0,-1.8,infoData.DayTime);
{ SetTextStyle(SmallFont,HorizDir,5);  }
 OutTextXYW(0,-1.95,'Heat with : '+HeatedPattern);
{ SetTextStyle(DefaultFont,HorizDir,1);  }
 OutTextXYW(0,-2.2,infoData.remarks);
 SetTextStyle(SmallFont,HorizDir,7);
 OutTextXYW(0,-2.4,file_name);
 SetTextStyle(DefaultFont,HorizDir,1);


 Nr := 1;
 NofData_ := freq * duration[Nr];
 ts := 0;
 tl := 0;
 for i:=1 to NofData do begin
  if KeyPressed then begin
   abort;
   if break then EXIT;
  end;
  psi := pos[i];
  if (abs(psi)<512) or (abs(psi)>1536) then ts:=ts+1 else tl:=tl+1;
  if i=NofData_ then begin
    if HeatedPattern='ม' then lambda := (ts-tl)/(tl+ts)
                         else lambda := (tl-ts)/(tl+ts);
    tl  := 0;
    ts  := 0;
    Bbr := duration[Nr];
    t   := NofData_/freq - Bbr;
    s := copy(name,length(name),1);
    if (s='A') or (s='a') then  n_ := 0;
    if (s='B') or (s='b') then  n_ := 3;
    if (s='C') or (s='c') then  n_ := 6;
    if (s='D') or (s='d') then  n_ := 9;
    if (s='E') or (s='e') then  n_ := 12;
 {
    if not s in ['a','A','b','B'] then begin
            CloseGraph;
            ClrScr;
            GotoXY(10,10);writeln('E R R O R  i n  f i l e n a m e !!');
            GotoXY(10,12);writeln('name must end with "a", "b", ..');
            repeat until KeyPressed;
            bu := ReadKey;
            EXIT;
    end;
}
    if ExpType[Nr+n_]=tr then SetFillStyle(CloseDotFill,yellow)
                      else SetFillStyle(LtSlashFill,yellow);
    barW(t,lambda,t+Bbr,0);
    rectangleW(t,lambda,t+Bbr,0);
    inc(Nr,1);
    NofData_ := NofData_ + freq*duration[Nr];
  end;
 end;
end;
{------------------------------------------------}
procedure SetRandomArenaPosition;
var  pos_ : integer;
begin
  sound(800);delay(100);NoSound;
  ArenaSpeed_on(1);
  ClosedLoop_off(1);
  if random>0.5 then dir := normal else dir := inverted;
  bias := dir*(350+random(300));
  SetArenaSpeed(1,2048+bias);
  delay(5000+random(3000));
  bias := dir*(350+random(300));
  SetArenaSpeed(1,2048-bias);
  delay(5000+random(3000));
  bias := 0;
  SetArenaSpeed(1,2048);
  ArenaSpeed_off(1);
  if ClosedLoop then ClosedLoop_on(1);
end;
{ ------------- Set ArenaPos(1) to next cold/hot boundary (optional)
begin
     pos_ := ArenaPos(1);
          if (pos_>=0) and (pos_<1025) then SetArenaPos(1,512);
          if (pos_>1024) and (pos_<2048) then SetArenaPos(1,1536);
          if (pos_>=-2048) and (pos_<-1024) then SetArenaPos(1,-1536);
          if (pos_>=-1024) and (pos_<0) then SetArenaPos(1,-512);
end;
}
{------------------------------------------------------------------}
procedure PrintOnScreen(Nr : integer; txt : str10; style : integer; color : byte);
begin
 if style=normal then begin
  TextBackground(blue);
  TextColor(color);
 end else begin
  TextBackground(white);
  TextColor(color);
 end;
  GotoXY(2+5*(Nr-1),line);write(txt);
  TextBackground(blue);
  TextColor(yellow);
end;
{*--------------------------------------------------------------------*}
procedure OnLineGraph2(tor,posi : real);
var    x,offs   : integer;
begin
  x := i mod 500;
  if x=1 then begin
   y0 := y0-100;
   if y0=-150 then y0 := 50
  end;
  if (i>1000) then offs := 1000 else offs := 0;
  y1old := torque[i-offs]/2048*80+Y0;
  y2old := pos[i-offs]/2048*50+Y0;
{  y2old := ArenaPos(1)/2048*50+Y0; fr replay Einstelltest}
  y1 := tor/2048*80 + y0;
  y2 := posi/2048*50 + y0;
  if x=1 then begin
   y11 := y1; y11old := y1old;
   y22 := y2; y22old := y2old;
  end;
   SetColor(yellow);
   lineW(x-1,y11old,x,y1old);
   if abs(y2old-y22old)<30 then lineW(x-1,y22old,x,y2old);
   SetColor(yellow);
   lineW(x-1,y11,x,y1);
   if abs(y2-y22)<30 then lineW(x-1,y22,x,y2);
   y11 := y1; y11old := y1old;
   y22 := y2; y22old := y2old;
end;
{*--------------------------------------------------------------------*}
procedure OnLineGraph3(tor,posi : real);
var    x,offs   : integer;
begin
  x := (i mod 300) + 250;
   y0 := -50;
  if (i>300) then offs := 300 else offs := 0;
  y1old := torque[i-offs]/2048*80+Y0;
  y2old := pos[i-offs]/2048*50+Y0;
  y1 := tor/2048*80 + y0;
  y2 := posi/2048*50 + y0;
  if x=251 then begin
   y11 := y1; y11old := y1old;
   y22 := y2; y22old := y2old;
  end;
   SetColor(blue);
   lineW(x-1,y11old,x,y1old);
   if abs(y2old-y22old)<30 then lineW(x-1,y22old,x,y2old);
   SetColor(col);
   lineW(x-1,y11,x,y1);
   if abs(y2-y22)<30 then lineW(x-1,y22,x,y2);
   y11 := y1; y11old := y1old;
   y22 := y2; y22old := y2old;
end;
{-------------------------------------------------}
procedure PrintMessage(message:string);
begin
  ClrScr;
  delay(100);
  sound(200);delay(500);NoSound;
  delay(150);
  sound(200);delay(500);NoSound;
  delay(150);
  sound(200);delay(500);NoSound;
  delay(150);
  sound(50);delay(2400);NoSound;
  GotoXY(24,10);
  writeln(message);
  repeat until KeyPressed;
  bu := ReadKey;
  ClrScr;
end;
{-------------------------------------------------}
function CheckFilename : word;
begin
 if (name='test-0X') or (length(name)<>7) then begin
  PrintMessage('you forgot the filename you fool!');
  CheckFileName := 1;
 end else CheckFileName := ok;
end;
{-------------------------------------------------}
function Replay(n1,n2:integer) : boolean;
begin
 replay := false;
 for n:=n1 to n2 do if ExpType[n]=rp then replay := true;
end;
{---------------------------------------------------------}
procedure TraceReplayPos;
var  dPsi : real;
begin
   dPsi := ArenaPos(1) - psi;
   if abs(dPsi) > 800 then dPsi := 0;
   bias := trunc(0.35*torque[i]+dpsi/2);
   SetArenaSpeed(1,2047 + bias);
end;
{-------------------------------------------------}
procedure ReplayMode;
begin
  psi  := pos[i];
  trq_ := 0;
  for n:=1 to k do begin
   TraceReplayPos;
   psi_ := ArenaPos(1);
   trq  := YawTorque;
   if (abs(psi_)<512) or (abs(psi_)>1536) then Sector := 1 else sector := 0;
   StepInto := Sector - OldSector;
   if StepInto= hot then begin
    if HeatedPattern = 'ย' then OpenShutter else CloseShutter;
   end;
   if StepInto=cold then begin
    if HeatedPattern = 'ย' then CloseShutter else OpenShutter;
   end;
   trq_ := trq_ + trq;
   OldSector := sector;
  end;
  trq_ := trq_/k;
  psi_ := psi;
  torque[i] := round(trq_);
  delay(2);
end;
{-------------------------------------------------}
procedure OperantMode;
begin
  psi_ := 0;
  trq_ := 0;
  for n:=1 to k do begin
   psi := ArenaPos(1);
   trq := YawTorque;
   if (abs(psi)<512) or (abs(psi)>1536) then Sector := 1 else sector := 0;
   StepInto := Sector - OldSector;
   if StepInto= hot then begin
    if HeatedPattern = 'ย' then OpenShutter else CloseShutter;
   end;
   if StepInto=cold then begin
    if HeatedPattern = 'ย' then CloseShutter else OpenShutter;
   end;
   psi_ := psi_ + psi;
   trq_ := trq_ + trq;
   OldSector := sector;
  end;
  trq_ := trq_/k;
  psi_ := psi_/k;
  torque[i] := round(trq_);
  pos[i]    := round(psi_);

  if (i=1) then begin
     fp:=0;
     NofPauses:=0;
  end;
  if (i>1) then begin
     inc(fp,1);
     NofPauses := NofPauses + abs(torque[i]-torque[i-1]);
     if (fp=20) then begin
         if (NofPauses<250) then begin
            if (AutoDetect=true) then blowfly else begin
             sound(1100);delay(250);NoSound;
             delay(200);
             sound(1100);delay(250);NoSound;
            end;
         end;   
         fp:=0;NofPauses:=0;
     end;
   end;

end;
{-------------------------------------------------}
procedure messen;   { Messen (german) = to get data (to do the experiment) }
begin
 break := false;
 if not (CheckFileName = ok) then exit;
 NofFiles := (NofPeriods div 3);
 if (NofPeriods mod 3) <> 0 then inc(NofFiles);
 for Nr:=1 to 15 do la[Nr] := '';
 Nr := 1;
for Fnr:=1 to NofFiles do begin
 if replay(Nr,Nr+2) then LoadReplayFile(Fnr);
  for n:=1 to 3 do begin
   for psi:= -125 to 125 do Histo[psi,n] := 0;
  end;
  HistoFrame;
  TimeTraceWindow;
  n_ := Nr mod 3; if n_=0 then n_ := 3;
 SetTextJustify(CenterText,CenterText);
 for n:=1 to Nr do begin
   StoreWorld(2,-48+40*(n-1),-113,-12+40*(n-1),-118);
   if WorldError then exit;
   RestoreWorld(2,-48+40*(n-1),-113,NotPut);
   FreeWorldMem(2);
   str(n,u);
   if ExpType[n]=tr then Col := Lightgreen;
   if ExpType[n]=te then Col := yellow;
   if (ExpType[n]=rp) or (ExpType[n]=nov) then Col := LightRed;
{   if Nr>1 then
   begin
    if ((Nr=8) and (ExpType[Nr-1]=tr)) then ChangePatterns;
    if ((Nr=9) and (ExpType[Nr-1]=rp)) then ChangePatterns;
   end;}
   SetColor(col);
   if (n<Nr) then OutTextXYW(-70+n*40,-103,la[n]);
 end;
 NofData  := freq*(duration[Nr]+duration[Nr+1]+duration[Nr+2]);
 NofData_ := freq*duration[Nr];
 if (ExpType[Nr]=tr) or (ExpType[Nr]=rp) then lampe_an else lampe_aus;
 if ExpType[Nr]=rp then begin
  k := 80;
  ClosedLoop_off(1);
  psi := pos[1];
  SetArenaPos(1,psi);
  ArenaSpeed_on(1);
 end else begin
  k := 145;
  psi := ArenaPos(1);
  ArenaSpeed_off(1);
  ClosedLoop_on(1);
 end;
 if (abs(psi)<512) or (abs(psi)>1526) then OldSector := 1 else OldSector := 0;
 if OldSector=1 then begin
    if HeatedPattern = 'ย' then OpenShutter else CloseShutter;
 end else begin
    if HeatedPattern = 'ย' then CloseShutter else OpenShutter;
 end;

 Xo := 400 - (n_ mod 2)*300;
 Yo :=  10 - (n_ div 3)*100;
 OutTextXYW(Xo,Yo-5,ExpType[Nr]);
 tl := 0;
 ts := 0;
 SetLineStyle(SolidLn,0,ThickWidth);
 if (ExpType[Nr]=te) or (ExpType[n]=nov) then SetRandomArenaPosition;
 t1 := time;

 for i := 1 to NofData do begin
  if KeyPressed then begin
   interrupt(2);
   if break then begin
    lampe_aus;
    CloseShutter;
    CloseGraph;
    EXIT;
   end;
  end;

  if ExpType[Nr]=rp then ReplayMode else OperantMode;

  if i=NofData_ then begin
   if HeatedPattern='ม' then lambda := (ts-tl)/(tl+ts)
    else lambda := (tl-ts)/(tl+ts);
   tl  := 0;
   ts  := 0;
   str(lambda:4:2,s);
   la[Nr] := s;
   OutTextXYW(-70+Nr*40,-103,s);
   inc(Nr,1);
   if Nr=16 then Nr := 15;
   n_ := Nr mod 3; if n_=0 then n_ := 3;
   Xo := 400 - (n_ mod 2)*300;
   Yo :=  10 - (n_ div 3)*100;
   if (Nr <= NofPeriods) then begin
    if (NofData_ < NofData) then begin
     NofData_ := NofData_ + freq*duration[Nr];
     if ExpType[Nr]=tr then col := LightGreen;
     if (ExpType[Nr]=rp) or (ExpType[Nr]=nov) then Col := LightRed;
{    if ((Nr=8) and (ExpType[Nr-1]=tr)) then ChangePatterns;
    if ((Nr=9) and (ExpType[Nr-1]=rp)) then ChangePatterns;}
     if (ExpType[Nr]=te) or (ExpType[Nr]=nov) then begin
     lampe_aus;
     SetRandomArenaPosition;
     end else lampe_an;
     if ExpType[Nr]=rp then begin
      ClosedLoop_off(1);
      k := 80;
      psi := pos[i+1];
      SetArenaPos(1,psi);
      ArenaSpeed_on(1);
      col := LightRed;
     end else begin
      ArenaSpeed_off(1);
      ClosedLoop_on(1);
      k := 145;
      if ExpType[Nr]=te then col := yellow else col := LightGreen;
     end;
     SetColor(col);
     OutTextXYW(Xo,Yo-5,ExpType[Nr]);
    end;
    StoreWorld(2,-48+40*(Nr-1),-113,-12+40*(Nr-1),-118);
    if WorldError then exit;
    RestoreWorld(2,-48+40*(Nr-1),-113,NotPut);
    FreeWorldMem(2);
   end;
  end;
  if (abs(psi)<512) or (abs(psi)>1536) then ts := ts+1 else tl := tl+1;
  psi := trunc(psi/2048*125);
  Y1 := Histo[psi,n_];
  Y2 := Y1 + 1;
  Histo[psi,n_] := trunc(Y2);
  SetLineStyle(SolidLn,0,ThickWidth);
  LineW(Xo+psi,Yo+0.7*Y1,Xo+psi,Yo+0.7*Y2);
  SetLineStyle(SolidLn,0,NormWidth);
  OnlineGraph3(trq_,psi_);
  delay(0);
 end;

 t2 := time;
(*******
 CloseGraph;
 ClrScr;
 GotoXY(10,15);
 writeln('E X P E R I M E N T   F I N I S H E D !');
 GotoXY(1,18);
 writeln(t1);
 writeln(t2);
 repeat until KeyPressed;
 bu := ReadKey;
*******)
 Sound(800); delay(200); NoSound;
 InfoData.date   := date;
 InfoData.DayTime := Uhr;
 if Fnr=NofFiles then begin
  StoreWorld(2,380,-77,525,-83);
{  if WorldError then exit; }
  RestoreWorld(2,380,-87,NormalPut);
  FreeWorldMem(2);
  SetTextJustify(RightText,CenterText);
  OutTextXYW(525,-90,'Press < ESC > to continue');
  SetTextJustify(LeftText,CenterText);
  repeat
   repeat until KeyPressed;
    bu := ReadKey;
   until bu=ESC;
   Toffs          := 0;
   indToffs       := 0;
   SetTorqueOffset(2048-Toffs);
end;
 CloseGraph;
 SaveData(true);
 delete(name,len+1,8-len);
 if (bu=ESC) then break := false;
 if break then EXIT;
end;  { for Fnr to NofFiles }
 lampe_aus;
 CloseShutter;
end;
{-------------------------------------------------}
Procedure DrawGrid;
begin
 TextBackground(blue);
 TextColor(yellow);
 ClrScr;
 GotoXY(1, 1);writeln('use arrow keys and del-key to change/choose conditions !');
 GotoXY(1, 2);writeln('( select replay-option with < R > )');
 GotoXY(1, 4);write('ฺฤฤฤฤ');for i:=1 to 14 do write('ยฤฤฤฤ');writeln('ฟ');
 GotoXY(1, 5);write('ณ    ');for i:=1 to 14 do write('ณ    ');writeln('ณ');
 GotoXY(1, 6);write('ภฤฤฤฤ');for i:=1 to 14 do write('มฤฤฤฤ');writeln('ู');
 GotoXY(1, 7);write('ณ              ณ              ณ              ณ              ณ              ณ');
 GotoXY(1, 8);write('ฺฤฤฤฤ');for i:=1 to 14 do write('ยฤฤฤฤ');writeln('ฟ');
 GotoXY(1, 9);write('ณ    ');for i:=1 to 14 do write('ณ    ');writeln('ณ');
 GotoXY(1,10);write('ภฤฤฤฤ');for i:=1 to 14 do write('มฤฤฤฤ');writeln('ู');
 GotoXY(1,11);write('ณ              ณ              ณ              ณ              ณ              ณ');
end;
{-------------------------------------------------}
procedure EnterTestSequence;
begin
 line := 9;
 Nr := 0;
 repeat inc(Nr,1) until (ExpType[Nr]='    ') or (Nr=15);
 NofPeriods := Nr;
 if (ExpType[Nr]='    ') then dec(NofPeriods);
 for Nr:=1 to NofPeriods do begin
  str(duration[Nr]:4,s);
  if s='   0' then s := '    ';
  PrintOnScreen(Nr,s,normal,yellow);
 end;
 if replay(1,NofPeriods) then begin
  line := 7;
  Nr   := 1;
  Fnr  := 1;
  repeat
   if replay(Nr,Nr+2) then begin
    PrintOnScreen(Nr,rp+':',normal,LightGreen);
    PrintOnScreen(Nr+1,' '+ReplayFile[Fnr],normal,LightRed);
   end;
   inc(Fnr);
   inc(Nr,3);
  until Fnr=6;
 end;
 line := 5;
 for Nr:=1 to NofPeriods do PrintOnScreen(Nr,ExpType[Nr],normal,yellow);
 Nr := 1;
 PrintOnScreen(Nr,ExpType[Nr],inverted,black);
 GotoXY(2+5*(Nr-1),line);
 repeat
 repeat b := ReadKey until b in ['R','r','n','N',#$48,#$4B,#$4D,#$50,#$53,chr(13)];
 case b of
  #$4B : begin        { left arrow }
          PrintOnScreen(Nr,ExpType[Nr],normal,yellow);
          dec(Nr,1);if Nr=0 then Nr := 15;
          PrintOnScreen(Nr,ExpType[Nr],inverted,black);
         end;
  #$4D : begin       { right arrow }
          PrintOnScreen(Nr,ExpType[Nr],normal,yellow);
          inc(Nr,1);if Nr=16 then Nr := 1;
          PrintOnScreen(Nr,ExpType[Nr],inverted,black);
         end;
  #$48 : begin       { arrow up }
          ExpType[Nr] := te;
          PrintOnScreen(Nr,ExpType[Nr],inverted,black);
         end;
  #$50 : begin       { arrow down }
          ExpType[Nr] := tr;
          PrintOnScreen(Nr,ExpType[Nr],inverted,black);
         end;
  'R','r': begin       { replay }
          ExpType[Nr] := rp;
          PrintOnScreen(Nr,ExpType[Nr],inverted,black);
         end;
  'N','n': begin       { replay }
          ExpType[Nr] := nov;
          PrintOnScreen(Nr,ExpType[Nr],inverted,black);
         end;

  #$53 : begin          { del }
          ExpType[Nr] := '    ';
          PrintOnScreen(Nr,ExpType[Nr],inverted,black);
         end;
 end;
 GotoXY(2+5*(Nr-1),line);
 TextBackground(blue);
 TextColor(yellow);
 until b=chr(13);
 PrintOnScreen(Nr,ExpType[Nr],normal,yellow);
 Nr := 0;
 repeat inc(Nr,1) until (ExpType[Nr]='    ') or (Nr=15);
 NofPeriods := Nr;
 if (ExpType[Nr]='    ') then dec(NofPeriods);
end;
{-------------------------------------------------}
function CheckReplayNames : word;
begin
 i := Fnr;
 k := Nr;
 Fnr  := 1;
 Nr   := 1;
 CheckReplayNames := ok;
 repeat
 if replay(Nr,Nr+2) then begin
  ReplFileName:=PathToData+ReplayFile[Fnr]+'.inf';
  if length(ReplayFile[Fnr])<8 then begin
   PrintMessage('wrong filename: '+ReplayFile[Fnr]+'  (must be 8 chars)');
   CheckReplayNames := 1;   { ok = 0 }
   i := Fnr; k := Nr;
  end else begin
   Assign(InfoFile,ReplFileName);
  {$I-}   Reset(InfoFile); {$I+}
   if (IOresult<>ok) then begin
    PrintMessage('Unknown replay-file: '+ReplayFile[Fnr]);
    CheckReplayNames := 1;   { ok = 0 }
    i := Fnr; k := Nr;
   end else Close(InfoFile);
  end;
 end;
 inc(Fnr);
 inc(Nr,3);
 until Fnr=6;
 Fnr := i;
 Nr  := k;
end;
{-------------------------------------------------}
procedure EnterReplayFileNames;
var ASCII : integer;
label MoveCursor;
begin
 line := 7;
 Nr   := 1;
 Fnr  := 1;
 repeat
  if replay(Nr,Nr+2) then begin
   PrintOnScreen(Nr,rp+':',normal,LightGreen);
   PrintOnScreen(Nr+1,' '+ReplayFile[Fnr],normal,LightRed);
   i := Nr; k := Fnr;
  end;
  inc(Fnr);
  inc(Nr,3);
 until Fnr=6;

 Nr   := i;
 Fnr  := k;

 repeat
 PrintOnScreen(Nr+1,'         ',normal,LightRed);
 PrintOnScreen(Nr+1,' '+ReplayFile[Fnr],inverted,black);
 b := ReadKey;
 MoveCursor:
 case b of
  #$4B : begin        { left arrow }
          PrintOnScreen(Nr+1,' '+ReplayFile[Fnr],normal,LightRed);
          dec(Nr,3);if Nr<0 then Nr := 13;
          dec(Fnr);if Fnr=0 then Fnr := 5;
{          PrintOnScreen(Nr+1,' '+ReplayFile[Fnr],inverted,black);  }
         end;
  #$4D : begin       { right arrow }
          PrintOnScreen(Nr+1,' '+ReplayFile[Fnr],normal,LightRed);
          inc(Nr,3);if Nr=16 then Nr := 1;
          inc(Fnr);if Fnr=6 then Fnr := 1;
{          PrintOnScreen(Nr+1,' '+ReplayFile[Fnr],inverted,black);  }
         end;
  #$08 : delete(ReplayFile[Fnr],length(ReplayFile[Fnr]),1);
  '0'..'9','A'..'Z','a'..'z','-','_' :
         if length(ReplayFile[Fnr])<8 then ReplayFile[Fnr] := ReplayFile[Fnr]+b;
  #$0D:  if CheckReplayNames <> ok then begin
          DrawGrid;
          line := 5;
          k := Nr;
          for Nr:=1 to NofPeriods do begin
           PrintOnScreen(Nr,ExpType[Nr],normal,yellow);
           if ((Nr mod 3) = 1) and replay(nr,nr+2) then begin
            line := 7;
            PrintOnScreen(Nr,rp+':',normal,LightGreen);
            PrintOnScreen(Nr+1,' '+ReplayFile[(Nr div 3)+1],normal,LightRed);
            line := 5;
           end;
          end;
          Nr := k;
          line := 7;
          b:='#'
         end;

  end;
 until b=chr(13);

 PrintOnScreen(Nr+1,' '+ReplayFile[Fnr],normal,LightRed);
end;
{-------------------------------------------------}
procedure EnterTimeIntervals;
begin
 line := 9;
 for Nr:=1 to NofPeriods do begin
  str(duration[Nr]:4,s);
  if s='   0' then s := '    ';
  PrintOnScreen(Nr,s,normal,yellow);
 end;
 Nr := 1;
 str(duration[Nr]:4,s);
  if s='   0' then s := '    ';
 PrintOnScreen(Nr,s,inverted,black);
 GotoXY(2+5*(Nr-1),line);

 repeat
 repeat b := ReadKey until b in [#$48,#$4B,#$4D,#$50,#$53,chr(13)];
 case b of
  #$4B : begin        { left arrow }
          str(duration[Nr]:4,s);
          if s='   0' then s := '    ';
          PrintOnScreen(Nr,s,normal,yellow);
          dec(Nr,1);if Nr=0 then Nr := 15;
          str(duration[Nr]:4,s);
          if s='   0' then s := '    ';
          PrintOnScreen(Nr,s,inverted,black);
         end;
  #$4D : begin       { right arrow }
          str(duration[Nr]:4,s);
          if s='   0' then s := '    ';
          PrintOnScreen(Nr,s,normal,yellow);
          inc(Nr,1);if Nr=16 then Nr := 1;
          str(duration[Nr]:4,s);
          if s='   0' then s := '    ';
          PrintOnScreen(Nr,s,inverted,black);
         end;
  #$48 : begin       { arrow up }
          duration[Nr] := duration[Nr]+15;
          str(duration[Nr]:4,s);
          if s='   0' then s := '    ';
          PrintOnScreen(Nr,s,inverted,black);
         end;
  #$50 : begin       { arrow down }
          duration[Nr] := duration[Nr]-15;
          if duration[Nr]<0 then duration[Nr] := 0;
          if s='   0' then s := '    ';
          str(duration[Nr]:4,s);
          PrintOnScreen(Nr,s,inverted,black);
         end;
  #$53 : begin          { del }
          duration[Nr] := 0;
          str(duration[Nr]:4,s);
          if s='   0' then s := '    ';
          PrintOnScreen(Nr,s,inverted,black);
         end;
 end;
 GotoXY(2+5*(Nr-1),line);
 TextBackground(blue);
 TextColor(yellow);
 until b=chr(13);
 for Nr:=1 to NofPeriods do begin
  if (Nr mod 3)=1 then TotalTime := 0;
  TotalTime := TotalTime + duration[Nr];
  if TotalTime>600 then begin
   sound(800);delay(100);NoSound;
   GotoXY(10,15);
   writeln('Total time per triple-block too large : ',TotalTime,'  ( maximum 600 s )');
   repeat until KeyPressed;
   GotoXY(10,15);ClrEol;
   EnterTimeIntervals;
  end;
 end;
end;
{-------------------------------------------------}
procedure SetupSequences;
var ASCII : integer;

begin
 DrawGrid;
 EnterTestSequence;
 if replay(1,NofPeriods) then EnterReplayFilenames;
 EnterTimeIntervals;

 repeat
   GotoXY(1,12);write('ณ              ณ              ณ              ณ              ณ              ณ');
   i := 1;
   name_ := copy(name,1,7);
   for Nr := 1 to NofPeriods do begin
    if (Nr mod 3)=1 then begin
     GotoXY(Nr*5,12);write(name_+chr(96+i));
     inc(i);
    end;
   end;
   GotoXY(5,15);write('< ESC >   back to main menue');
   GotoXY(5,17);write('<  N  >   basic filename (must be 7 letters) : ',name);
   GotoXY(5,18);write('          (will be extended with a, b, c, ...)');
   GotoXY(5,21);write('< F > fly     : ',infoData.fly);
   GotoXY(5,22);write('< R > remarks : ');
   GotoXY(21,22);write(InfoData.remarks);
   GotoXY(1,1);
 repeat ch := ReadKey until UpCase(ch) in [ESC,'N','F','R'];
 case UpCase(ch) of
 'N' : begin
        repeat
          repeat
           GotoXY(52,17);write('        ');
           GotoXY(52,17);write(name);
           bu := readkey;
           ASCII := ord(bu);
           case ASCII of
            8 : delete(name,length(name),1);
            13: { do nothing };
           else  name := name+bu;
           end;
         until ASCII = 13;
         len := length(name);
        until len=7;
       end;
 'F':  begin
        GotoXY(21,21);ClrEol;
        readln(InfoData.fly);
       end;
 'R':  begin
        GotoXY(21,22);ClrEol;
        readln(InfoData.remarks);
       end;
  end;
 until ch=ESC;
end;
{-------------------------------------------------}
procedure PrintRedLetters;
begin

  TextColor(LightRed);
  GotoXY(14, 8);write('S');
  GotoXY(14,10);write('A');
  GotoXY(14,11);write('W');
  GotoXY(14,12);write('R');
  GotoXY(55,12);write('N');
  GotoXY(14,14);write('O');
  GotoXY(14,15);write('T');
  GotoXY(14,16);write('P');
  GotoXY(14,17);write('I');
  GotoXY(14,18);write('H');
  GotoXY(14,19);write('U');
  GotoXY(14,21);write('D');
  GotoXY(14,22);write('E');
  GotoXY(14,24);write('Q');
  GotoXY(46,24);write('X');
  GotoXY(55,15);writeln('CTRL-T');
  GotoXY(55,16);writeln('CTRL-P');
  GotoXY(55,17);writeln('CTRL-I');

  TextColor(white);
  GotoXY(19, 8);write('S');
  GotoXY(20,10);write('A');
  GotoXY(19,11);write('W');
  GotoXY(19,12);write('R');
  GotoXY(64,12);write('N');
  GotoXY(19,14);write('O');
  GotoXY(19,15);write('T');
  GotoXY(19,16);write('P');
  GotoXY(22,17);write('I');
  GotoXY(19,18);write('H');
  GotoXY(21,19);write('U');
  GotoXY(19,21);write('D');
  GotoXY(25,22);write('E');
  GotoXY(19,24);write('Q');
  TextColor(LightGreen);
  GotoXY(34,10);write(PathToData);
  GotoXY(71,12);write(name);
  GotoXY(28,18);write(heat);
  GotoXY(28,19);write(shut);
  GotoXY(47,21);writeln(ExpDisp);
  TextColor(yellow);
end;
{-------------------------------------------------}
procedure menue;
begin
  TextBackground(blue);
  TextColor(yellow);
  ClrScr;
  GotoXY( 3, 1);writeln(date);
  GotoXY(17, 2);writeln('ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ');
  GotoXY(17, 3);writeln('ณ    ÜÜÜÜÜÜ      ÜÜ      ÜÜÜÜÜÜ      ÜÜ      ณ');
  GotoXY(17, 4);writeln('ณ    ฿฿ÛÛ฿฿      ÛÛ      ฿฿ÛÛ฿฿      ÛÛ      ณ');
  GotoXY(17, 5);writeln('ณ      ÛÛ      ÛÛÛÛÛÛ      ÛÛ      ÛÛÛÛÛÛ    ณ  Operant');
  GotoXY(17, 6);writeln('ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู  Training');
  GotoXY(12, 8);writeln('< S >  Setup Training/Test-Periods');
  GotoXY(12,10);writeln('< A >  pAth to data : ',PathToData);
  GotoXY(12,11);writeln('< W >  WriteDataFile (SaveData)');
  GotoXY(12,12);writeln('< R >  ReadDataFile');
  GotoXY(53,12);writeln('< N >  FileName : ',name);
  GotoXY(12,14);writeln('< O >  Oscilloscope-Simulation');
  GotoXY(12,15);writeln('< T >  TimeTraces              HPLJ III: < CTRL-T >');
  GotoXY(12,16);writeln('< P >  Plot PreferenceIndex    HardCopy: < CTRL-P >');
  GotoXY(12,17);writeln('< I >  PosItion-Histograms     HardCopy: < CTRL-I >');
  GotoXY(12,18);writeln('< H >  Heater  :',heat);
  GotoXY(12,19);writeln('< U >  ShUtter :',shut);
  GotoXY(12,21);writeln('< D >  Display during Experiment : ',ExpDisp);
  GotoXY(12,22);writeln('< E >  START EXPERIMENT');
  GotoXY(12,24);writeln('< Q >  Q U I T                  < X >  Heat with');
  PrintRedLetters;
  TextColor(lightGreen);
  if HeatedPattern = 'ย' then begin
   GotoXY(65,23);ClrEol;writeln('ÜÜÜ');
   GotoXY(65,24);ClrEol;writeln(' Û ');
  end else begin
   GotoXY(65,23);ClrEol;writeln(' Ü ');
   GotoXY(65,24);ClrEol;writeln('ÜÛÜ');
  end;
  TextColor(yellow);

  repeat
   repeat
    if Uhr <> DayTime then begin
     DayTime := Uhr;
     GotoXY(60,1);ClrEol;writeln(DayTime);
     GotoXY( 1,24);
    end;
   until KeyPressed;
   c := ReadKey
  until UpCase(c) in MenueItems;
  case UpCase(c) of
  'S' : SetupSequences;
  'W' : SaveData(false);          { not AutoSave }
  'R' : ReadFile;
  'N' : begin
         EnterFileName;
        end;
  'A' : begin
         GotoXY(34,10);ClrEol;
         readln(PathToData);
         if copy(PathToData,length(PathToData),1)<>'\'
            then PathToData := PathToData+'\';
  {       PathToData := 'c:\brembs\'+PathToData;  }
        end;
  'O' : FlyMonitor;
  'T' : begin
         TimeTraces;
         if not break then repeat until KeyPressed;
         CloseGraph;
        end;
  'P' : begin
         PlotHisto;
         if not break then repeat until KeyPressed;
         CloseGraph;
        end;
  'I' : begin
         PositionHisto;
         if not break then repeat until KeyPressed;
         CloseGraph;
        end;
  chr(20) : begin
             PlotTimeTraces;
            end;
  chr(16) : begin
             PlotHisto;
             HardCopy(small,HighDensity);
          {   HardCopy(false);  }
             CloseGraph;
            end;
  chr(9)  : begin
             PositionHisto;
             HardCopy(small,HighDensity);
          {   HardCopy(false);  }
             CloseGraph;
            end;
  'H' : begin
         if heat=' off' then begin
          lampe_an;
          heat := ' on ';
         end else begin
          lampe_aus;
          heat := ' off';
         end;
        end;
  'U' : begin
         if shut=' closed' then begin
          OpenShutter;
          shut := ' open';
         end else begin
          CloseShutter;
          shut := ' closed';
         end;
        end;
  'E' : begin
          NofPauses:= 0;
          Toffs          := 0;
          indToffs       := 0;
          SetTorqueOffset(2048-Toffs);
          messen;
        end;
  'D' : begin
          if ExpDisp='TimeTraces' then ExpDisp := 'Histograms'
                                 else ExpDisp := 'TimeTraces';
        end;
  'X' : if HeatedPattern='ย' then HeatedPattern := 'ม'
                             else HeatedPattern := 'ย';
{----------
  'Y' : readln(t0);
  'K' : readln(k_);
-----------}
  'Q' : quit := true;
  end;
end;
{-------------------------------------------------}
procedure InitProgram;
begin
  TextBackground(blue);
  TextColor(yellow);
  ResetML;
  quit       := false;
  break      := false;
  for Nr:=0 to 15 do SetRelais(Nr,false);
  randomize;
  SetArenaSpeed(1,2048);
  Toffs          := 0;
  indToffs       := 0;
  SetTorqueOffset(2048-Toffs);
  ArenaSpeed_off(1);
  ClosedLoop_off(1);
  lampe_aus;
  CloseShutter;
  bias           := 0;
  loop           := 'open loop';
  ClosedLoop     := false;
  HeatedPattern  := 'ย';
  MenueItems :=
   ['I','N','S','W','R','A','O','T','P','H','U','E','D','X','Q',{'K','Y',}
    chr(9),chr(16),chr(20),chr(26)];
  tr         := ' tr ';     { training }
  te         := 'test';
  rp         := 'repl';     {  replay  }
  nov        := 'novl';     {  novelty }
  for Nr := 1 to 9 do begin
   if (Nr<3) or (Nr=5) or (Nr>7) then ExpType[Nr] := te
                               else ExpType[Nr] := tr;
   duration[Nr] := 120;
  end;
  for Nr:=10 to 15 do begin
    ExpType[Nr]     := '    ';
    duration[Nr]   := 120;
  end;
  for Nr:=1 to 5 do ReplayFile[Nr] := '';
  TotalTime      := 360;
  freq           := 20;             { 20 Hz sampling rate }
  NofData        := 7200;
  NofRecs        := 6;
  NofPeriods     := 15;
  heat           := ' off';
  shut           := ' closed';
  ExpDisp        := 'Histograms';
  ok             := 0;
  name           := 'test-0X';
  PathToData     := 'c:\brembs\';
  InfoData.remarks := '';
  InfoData.fly   := '';
  bu := 'X';
  t0 := -1.5;           { used in procs 'TimeTraces' and 'DebugPosTrace' }
  k_ := 10.5;
{  SetIntegratorZero(1);  }
{ setRelais(3,false);
 setRelais(4,true);
 setRelais(5,true);
 repeat
  GotoXY(5,5);ClrEol;writeln(yawTorque);
 until KeyPressed;
 repeat
  sum := 0;
  for i:=1 to 500 do
   sum := sum + ArenaPos(1);
  sum := sum/500;
  GotoXY(5,5);ClrEol;
  writeln(sum:4:0);
 until KeyPressed;  }
 { if MaxAvail < 57600 then begin
    ClrScr;
    writeln('not enough memory :',MaxAvail);
    repeat until KeyPressed;
  end;  }

end;
{-------------------------------------------------}
begin
  InitProgram;
  repeat menue until quit = true;
  ClrScr;
  ClosedLoop_off(1);
end.
