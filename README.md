# Send-Signal
To compile the program simply run:
  make send_signals
  
Running the program: <br/>
  send_signals -p process_name -s signal_type <br/>
  -p process name - process name to which the signal is to be sent <br/>
  -s signal_type - either name of signal (i.e SIGKILL) or a number that indicates signal number in the system <br/>
   providing wrong signal signature will or nonexsitng process name will yield an error <br/>
<br/>  
Current version of the program allows to send one signal to process indentified by given name (f.e check ps au)<br/>
if there are more than one processes under the same name the program shall send signal to the one with the lowest ID (usually meaning parent process).<br/>
<br/>
Further iterations of this software will include:<br/>
  - timed signall sending and sending of multipe signals<br/>
  - choosing signals from tree of signals<br/>
  - extending the range of signals handled by the program<br/>
