Unit Timedate;
(*************************************************************************)
interface
  uses dos;
  type DateStr    = string[40];
       TimeString = string[40];
       NameString = string[8];
  function Date         : DateStr;
  function time         : TimeString;
  function watch        : TimeString;
  function AutoFileName : NameString;
implementation
(*------------------------------------------------------------------------*)
function Date:DateStr;
type strtype = string[10];
const Monat : array[1..12] of strtype =('January','February','March','April','Mai',
          'June','July','August','September','October','November','December');
      Tag   : array[0..6] of strtype =('Sunday','Monday','Tuesday','Wednesday',
              'Thursday','Friday','Saturday');

var year,Month,Day,DayofWeek:word;
    year_str      : string[4];
    Month_str     : string[12];
    Day_str       : string[2];
    DayofWeek_str : string[10];
begin
    GetDate(Year,Month,Day,DayofWeek);
    str(Year,year_str);
    str(day,day_str);
    Month_str := Monat[Month];
    DayofWeek_str:=Tag[DayofWeek];
    date:= DayofWeek_str+' '+Day_str+' '+Month_str+' '+Year_str;
end;
(*------------------------------------------------------------------------*)
function time:TimeString;
var
  hour_str,min_str,second_str,sec100_str:     string[2];
  hour,min,second,sec100                :     word;
begin
    GetTime(Hour,min,Second,sec100);
    str(Hour,Hour_str);
    str(min,min_str);
    str(second,second_str);
    str(sec100,sec100_str);
  time := hour_str+' h '+min_str+' m '+second_str+
         '.'+sec100_str+' s';
end;
(*------------------------------------------------------------------------*)
function watch : timeString;
var
  hour_str,min_str,second_str           :     string[2];
  hour,min,second,sec100                :     word;
begin
    GetTime(Hour,min,Second,sec100);
    str(Hour,Hour_str);
    str(min,min_str);
    str(second,second_str);
  watch := hour_str+' h '+min_str+' m '+second_str+' s';
end;
(*------------------------------------------------------------------------*)
function AutoFileName : NameString;
begin

end;
(*------------------------------------------------------------------------*)
end.
