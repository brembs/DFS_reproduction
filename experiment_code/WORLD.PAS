unit world;
interface

procedure DefineWorld(Xmin,Ymin,Xmax,Ymax : real);
procedure DrawFrame;
function Xp(x : real) : integer;
function Yp(y : real) : integer;
function Rp(radius : real) : integer;
procedure SetViewportW(x1,y1,x2,y2 : integer; clip : boolean);
procedure lineW(x1,y1,x2,y2 : real);
procedure LineToW(x,y : real);
procedure MoveToW(X,Y : real);
procedure RectangleW(X1,Y1,X2,Y2 : real);
procedure BarW(x1,y1,x2,y2 : real);
procedure arcW(x,y: real; StAngle,EndAngle : word; radius : real);
procedure PieSliceW(x,y: real; StAngle,EndAngle : word; radius : real);
procedure CircleW(x,y,radius : real);
procedure PutPixelW(X,Y : real; Pixel : word);
function GetPixelW(X,Y : real) : word;
procedure OutTextXYW(x,y : real; TextString : string);
procedure SetPosW(x,y : real);
procedure StoreWorld(Nr : integer; X1,Y1,X2,Y2 : real);
procedure RestoreWorld(Nr : integer; X1,Y1 : real; PutType : word);
procedure FreeWorldMem(Nr : integer);

var WorldError : boolean;

implementation
uses graph,crt,mouse;

var
     Xo_UserAxis,Yo_UserAxis,
     XaxisScale,YaxisScale              : real;
     XmaxGlb,YmaxGlb                    : integer;
     ImgPntr                            : array[1.. 10] of pointer;
     WorldSize                          : array[1.. 10] of LongInt;
{------------------------------------------------------------}
procedure DefineWorld(Xmin,Ymin,Xmax,Ymax : real);
begin
  XmaxGlb := GetMaxX;
  YmaxGlb := GetMaxY;
  XaxisScale := XmaxGlb/(Xmax-Xmin);        
  YaxisScale := YmaxGlb/(Ymax-Ymin);
  Xo_UserAxis:= -Xmin * XaxisScale;
  Yo_UserAxis:=  Ymax * YaxisScale;
end;
{------------------------------------------------------------}
procedure DrawFrame;
begin
 Rectangle(0,0,GetMaxX,GetMaxY);
end;
{------------------------------------------------------------}
function Xp(x : real) : integer;
var  z : integer;
begin
  z := round(Xo_UserAxis + XaxisScale * x);
  if z>XmaxGlb then z:= XmaxGlb;
  if z<0 then z := 0;
  Xp := z;
end;
{------------------------------------------------------------}
function Yp(y : real) : integer;
var  z : integer;
begin
  z := round(Yo_UserAxis - YaxisScale * y);
  if z>YmaxGlb then z:= YmaxGlb;
  if z<0 then z := 0;
  Yp := z;
end;
{------------------------------------------------------------}
function Rp(radius : real) : integer;
begin
  rp := round(XaxisScale * radius);
end;
{------------------------------------------------------------}
procedure SetViewportW(x1,y1,x2,y2 : integer; clip : boolean);
begin
  SetViewport(xp(x1),yp(y1),xp(x2),yp(y2),clip);
end;
{------------------------------------------------------------}
procedure lineW(x1,y1,x2,y2 : real);
begin
 line(xp(x1),yp(y1),xp(x2),yp(y2));
end;
{------------------------------------------------------------}
procedure LineToW(x,y : real);
begin
 LineTo(Xp(x),Yp(y));
end;
{------------------------------------------------------------}
procedure MoveToW(X,Y : real);
begin
 MoveTo(Xp(x),Yp(y));
end;
{------------------------------------------------------------}
procedure RectangleW(X1,Y1,X2,Y2 : real);
begin
 rectangle(Xp(x1),Yp(y1),Xp(x2),Yp(y2));
end;
{------------------------------------------------------------}
procedure BarW(x1,y1,x2,y2 : real);
begin
 bar(Xp(x1),Yp(y1),Xp(x2),Yp(y2));
end;
{------------------------------------------------------------}
procedure arcW(x,y: real; StAngle,EndAngle : word;radius : real);
begin
 arc(Xp(x),Yp(y),StAngle,EndAngle,rp(radius));
end;
{------------------------------------------------------------}
procedure PieSliceW(x,y: real; StAngle,EndAngle : word;radius : real);
begin
 PieSlice(Xp(x),Yp(y),StAngle,EndAngle,rp(radius));
end;
{------------------------------------------------------------}
procedure CircleW(x,y,radius : real);
begin
 circle(Xp(x),Yp(y),Rp(radius));
end;
{------------------------------------------------------------}
procedure PutPixelW(X,Y : real; Pixel : word);
begin
 PutPixel(Xp(x),Yp(y),Pixel);
end;
{------------------------------------------------------------}
function GetPixelW(X,Y : real) : word;
begin
 GetPixelW := GetPixel(Xp(x),Yp(y));
end;
{------------------------------------------------------------}
procedure OutTextXYW(x,y : real; TextString : string);
begin
 OutTextXY(Xp(x),Yp(y),TextString);
end;
{------------------------------------------------------------}
procedure SetPosW(x,y : real);
begin
  SetPos(Xp(x),Yp(y));
end;
{------------------------------------------------------------}
procedure StoreWorld(Nr : integer; X1,Y1,X2,Y2 : real);
var MaxMem  : LongInt;
begin
  WorldError := false;
  WorldSize[Nr] := ImageSize(xp(X1),yp(Y1),xp(X2),yp(Y2));
  MaxMem := MaxAvail;
  if (WorldSize[Nr]>0) and (WorldSize[Nr]<MaxMem) then begin
   GetMem(ImgPntr[Nr],WorldSize[Nr]);
   GetImage(xp(X1),yp(Y1),xp(X2),yp(Y2),ImgPntr[Nr]^);
  end else begin
   CloseGraph;
   ClrScr;
   writeln('world size too large : ',WorldSize[Nr]);
   writeln('available : ',MaxMem,' bytes');
   writeln('press any key');
   WorldError := true;
   repeat until KeyPressed;
  end;
end;
{------------------------------------------------------------}
procedure RestoreWorld(Nr : integer; X1,Y1 : real; PutType : word);
begin
   PutImage(xp(X1),yp(Y1),ImgPntr[Nr]^,PutType);
end;
{------------------------------------------------------------}
procedure FreeWorldMem(Nr : integer);
begin
   FreeMem(ImgPntr[Nr],WorldSize[Nr]);
end;
{------------------------------------------------------------}
end.


