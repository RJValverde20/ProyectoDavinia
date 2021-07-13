/*	Proyecto Davinia | login.h
	En este fichero se inicia sesi�n. Es decir, valida el usuario ingresado
con el creado anteriormente.
*/

// Valida usuario
void loginFunc(void) {
	char _char;
	// Abre los ficheros correspondientes
	username = fopen("./ficheros/username.txt", "r");
	passwd = fopen("./ficheros/passwd.txt", "r");
	
	clearScreen();
	puts("\tIniciar Sesi�n");
	puts("\t~~~~~~~~~~~~~~");
	printf("\tNOMBRE\t: ");
	fflush(stdin);
	scanf("%s", usuario);
	
	printf("\tCLAVE\t: ");
	// Detectar OS soportado (Windows y Linux)
	if (strcmp(OS, "Windows") == 0) {
		// Pedir clave y ocultarla (Windows)
		requestAndHidePasswdWinFunc();
	} else if (strcmp(OS, "Linux") == 0) {
		// Pedir clave y ocultarla (Linux)
		requestAndHidePasswdLnxFunc();
	} else {
		printf("Error: Sistema operativo no soportado.");
		exit(EXIT_FAILURE);
	}
	
	// Verificar nombre de usuario
	_char = fgetc(username);
	i = 0;
	while (usuario[i]) {
		if (usuario[i] != _char) {
			clearScreen();
			printf("\nError: Nombre o contrase�a incorrecta.\nIntente m�s tarde.");
			exit(EXIT_SUCCESS);
		}
		_char = fgetc(username);
		++i;
	}
	// Verificar contrase�a
	_char = fgetc(passwd);
	i = 0;
	while (clave[i]) {
		if (clave[i] != _char) {
			clearScreen();
			printf("\nError: Nombre o contrase�a incorrecta.\nIntente m�s tarde.");
			exit(EXIT_SUCCESS);
		}
		_char = fgetc(passwd);
		++i;
	}
	fclose(username);
	fclose(passwd);
	clearScreen();
}
