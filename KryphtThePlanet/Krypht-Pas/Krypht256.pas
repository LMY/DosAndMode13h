{$I ktools.pas}

var  sorg,dest : file ;
     keyt,keyt2,keyt3,key,keyn : array[1..256] of byte ; 
     unkry,kry : array [1..32] of byte ; 
     dim,dim8,i,k : byte ; 
     unkrybin,krybin,kbin : array [1..256] of byte ;
     x,f : integer ;
     temp : string ;
     

begin
     if paramcount <> 2 then 
     begin
          writeln ('Krypht [file] [keyfile]') ;
          halt ;
     end ;
     assign(sorg,paramstr(1)) ;
     temp := paramstr(1) ;
     for i := 1 to ord(temp[0]) do if temp[i] = '.' then temp[0] := chr(i);
     temp := temp + 'kyp' ;    
     assign(dest,temp) ;
     loadkey(paramstr(2),256,key);
     reset(sorg,1);
     rewrite(dest,1);
     repeat
          blockread(sorg,unkry,32,x);          
          if x <> 0 then
          begin
               case f of 
               1 : inc(f) ;
               2 : begin                                                                                 {Il case serve per la gestione progressiva delle kiavi}
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
               if (x < 8) then 
               begin
                    k := 1 ;
                    for i := 1 to 256 do 
                    begin
                         if key[i] <= x*8 then                                                                {Adatta la kiave alla lunghezza dell'ultimo pezzo di file}
                         begin
                              keyn[k] := key[i] ;
                              inc (k) ;
                         end ;
                    end ;
                    for i := 1 to k do key[i] := keyn[i] ;
               end ;
               db(unkry,x,unkrybin);
               {LMY Krypht}
               for i := 1 to x*8 do kbin[i] := unkrybin[key[i]] ;                                       
               {K Krypht}
               krybin[key[1]] := kbin[key[x*8]] ;                                                        
               for i := 1 to x*8-1 do krybin[key[i+1]] := kbin[key[i]] ;
               bd(krybin,x,kry);
               blockwrite(dest,kry,x);
          end ;
     until x < 32 ;
     close(sorg) ;
     close(dest) ;
end.
          

          
          

     

