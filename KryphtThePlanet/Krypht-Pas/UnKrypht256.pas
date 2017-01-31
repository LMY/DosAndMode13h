{$I ktools.pas}

var  sorg,dest : file ;
     keyt,keyt2,keyt3,key,keyn : array[1..256] of byte ; 
     unkry,kry : array [1..32] of byte ; 
     dim,dim8,i,k : byte ; 
     unkrybin,krybin,kbin : array [1..256] of byte ;
     x,f : integer ;

begin
     if paramcount <> 3 then 
     begin
          writeln ('UnKrypht [file] [new file] [keyfile]') ;
          halt ;
     end ;
     assign(sorg,paramstr(1)) ;
     assign(dest,paramstr(2)) ;
     loadkey(paramstr(3),256,key);
     reset(sorg,1);
     rewrite(dest,1);
     repeat
          blockread(sorg,kry,32,x);          
          if x <> 0 then
          begin
               case f of 
               1 : inc(f) ;
               2 : begin                                                                                   {Il case è per la gesione progressiva delle kiavi}
                         inc(f);
                         for i := 1 to 256 do keyt[i] := key[key[i]];
                         keyt2[key[1]] := keyt[key[256]];
                         for i := 1 to 255 do keyt2[key[i+1]] := keyt[key[i]];
                         for i := 1 to 256 do keyt[i] := key[i] ;
                         for i := 1 to 256 do key[i] := keyt2[i] ;
                    end ;
               3 : begin
                         for i := 1 to 256 do keyt2[i] := key[keyt[i]];
                         keyt3[keyt[1]] := keyt2[keyt[256]];
                         for i := 1 to 255 do keyt3[keyt[i+1]] := keyt2[keyt[i]];
                         for i := 1 to 256 do keyt[i] := key[i] ;
                         for i := 1 to 256 do key[i] := keyt3[i] ;
                   end ;
               end ;
               if (x < 32) then 
               begin
                    k := 1 ;
                    for i := 1 to 256 do 
                    begin
                         if key[i] <= x*8 then                                                               {Taglia la kiave se il pezzo di file è più korto}
                         begin
                              keyn[k] := key[i] ;
                              inc (k) ;
                         end ;
                    end ;
                    for i := 1 to k do key[i] := keyn[i] ;
               end ;
               db(kry,x,krybin);
               {K Krypht}
               kbin[key[x*8]] := krybin[key[1]] ;
               for i := 2 to x*8 do kbin[key[i-1]] := krybin[key[i]];
               {LMY Krypht}
               for i := 1 to x*8 do
               unkrybin[key[i]] := kbin[i] ;
               bd(unkrybin,x,unkry);
               blockwrite(dest,unkry,x);
          end ;
     until x < 32 ;
     close(sorg) ;
     close(dest) ;
end.
          

          
          

     

