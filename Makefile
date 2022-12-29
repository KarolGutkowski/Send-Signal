send_signals: send_signals.c process_sig.c
	gcc -Wall -fsanitize=address,undefined -o send_signals send_signals.c process_sig.c

