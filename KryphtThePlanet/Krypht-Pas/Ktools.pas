function elev(n,e : byte) : byte ;
var i,t : byte ;
begin
     t := 1 ;
     for i := 1 to e do t := t * n ;
     elev := t ;
end ;
     
procedure bd(b : array of byte ; l:byte ;var n : array of byte) ;
var i,k,j : byte ;
var t : array [0..32,0..7] of byte ;
begin
     for i := 0 to l*8-1 do t[i div 8 ,i mod 8] := b[i] ;
     for i := 0 to l-1 DO
     begin
          n[i] := 0 ;
          for j := 7 downto 0 do
          n[i] := n[i] + t[i,j]*elev(2,7-j) ;
     end;
end ;

procedure db(n : array of byte ; l:byte ; var b : array of byte) ;
var i,k : byte ;
begin
     for k := 0 to l-1 do
     begin
          for i := 7 downto 0 do
          begin
               b[i+k*8] := n[k] mod 2 ;
               n[k] := n[k] div 2 ;
          end ;
     end ;
end ;

procedure loadkey(fn : string ; dim : byte ; var key : array of byte) ;
var kf : file ;
    x : integer ;
    
begin
     assign (kf,fn) ;
     reset (kf,1) ;
     blockread (kf,key,dim,x) ;
     close (kf) ;
end ;

