
final: finalmain.o finalfn.o
	gcc finalmain.o finalfn.o -lX11 gfx4.o -lm -o final

finalmain.o: finalmain.c finalfn.h
	gcc -c finalmain.c -o finalmain.o

finalfn.o: finalfn.c
	gcc -c finalfn.c -o finalfn.o

clean:
	rm *.o final 