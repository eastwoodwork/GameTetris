# myTetris
Only 2.9KB code. Based on 8-bit MCU (AT89C52/51) &amp; 8 x 16 LED Matrix.<br>
Code migration to 16/32-bit MCUs or other LED matrix size only need to modify a few micro definition.<br>
you can change ROW/COL value to suit your LED matrix size:<br>
&nbsp; #define ROW 16<br>
&nbsp; #define COL 8<br>
you can change MCUBITS value based on the MCU you use:<br>
&nbsp; #define MCUBITS 8<br>
Of course, following ports related to LED matrix may also need to modify if you enlarge the matrix size:<br>
&nbsp; #define PORT_SEG0 P2<br>
&nbsp; #define PORT_SEG1 P1<br>
&nbsp; #define PORT_SCAN P0<br>
&nbsp; #define PORT_KEYS P3<br>
Or all you need is just to rewrite a LED matrix driver. <br>
Have fun!<br>
