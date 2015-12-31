# QuadCopter_PP<br>
Main Repository for all code for the Quadcopter Project.<br>
Personal Project 2015/16 IICS<br>
<br>
All code for various Pic Microcontrollers programmed in either XC8 or XC32. <br>
<br>
Naming Scheme:<br>
&nbsp;PPQCU_{RC/QCU}_[Processor Name]<br>
<br>
<b>Key:</b><br>
&nbsp;PPQCU: <br>
&nbsp;&nbsp;Project Handle (<b>P</b>ersonal <b>P</b>roject <b>Q</b>uad<b>C</b>opter <b>C</b>ontrol <b>U</b>nit)<br>
&nbsp;RC / QCU:<br>
&nbsp;&nbsp;Location of the MicroController associated with the programm.<br>
&nbsp;&nbsp;&nbsp;RC: The MicroController is located on the Remote Control<br>
&nbsp;&nbsp;&nbsp;QCU: The MicroController is located on the Control Unit on the Quadcopter<br>
&nbsp;Processor Name:<br>
&nbsp;&nbsp;Name of the Processor<br>
<br>
<br>	
<b>Programs Included:</b><br>
&nbsp;PPQCU_CU_MAIN:<br>
&nbsp;&nbsp;MicroController:<br>
&nbsp;&nbsp;&nbsp;PIC32MX120F064H<br>
&nbsp;&nbsp;Language/Compiler:<br>
&nbsp;&nbsp;&nbsp;Programmed in C using the XC32 Complier.<br>
&nbsp;&nbsp;MicroController Purpose:<br>
&nbsp;&nbsp;&nbsp;Main processor on the Control Unit<br>
<br>
&nbsp;PPQCU_CU_BATSENSE:<br>
&nbsp;&nbsp;MicroController:<br>
&nbsp;&nbsp;&nbsp;PIC12F1840<br>
&nbsp;&nbsp;Language/Compiler:<br>
&nbsp;&nbsp;&nbsp;Programmed in C using the XC8 Complier<br>
&nbsp;&nbsp;MicroController Purpose:<br>
&nbsp;&nbsp;&nbsp;Battery Level Sensing, and low battery warning<br>
<br>
&nbsp;PPQCU_CU_INTERFACE:<br>
&nbsp;&nbsp;MicroController:<br>
&nbsp;&nbsp;&nbsp;PIC12F1840<br>
&nbsp;&nbsp;Language/Compiler:<br>
&nbsp;&nbsp;&nbsp;Programmed in C using the XC8 Complier<br>
&nbsp;&nbsp;MicroController Purpose:<br>
&nbsp;&nbsp;&nbsp;Interfacing to the ESC and, in turn, the motors.<br>
<br>
&nbsp;PPQCU_CU_LIGHTS:<br>
&nbsp;&nbsp;MicroController:<br>
&nbsp;&nbsp;&nbsp;PIC12F1840<br>
&nbsp;&nbsp;Language/Compiler:<br>
&nbsp;&nbsp;&nbsp;Programmed in C using the XC8 Complier<br>
&nbsp;&nbsp;Controller Purpose:<br>
&nbsp;&nbsp;&nbsp;UI on the QuadCopter<br>
<br>	
&nbsp;PPQCU_RC_REMOTE:<br>
&nbsp;&nbsp;MicroController:<br>
&nbsp;&nbsp;&nbsp;PIC18F26K22<br>
&nbsp;&nbsp;Language/Compiler:<br>
&nbsp;&nbsp;&nbsp;Programmed in C using the XC8 Complier<br>
&nbsp;&nbsp;MicroController Purpose:<br>
&nbsp;&nbsp;&nbsp;Main Processor on the Remote Controller<br>