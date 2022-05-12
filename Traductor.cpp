#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;
const char *nombre_archivo = "archivo.dat";
const char *nombre_archivo_temp = "archivo_aux.dat";
int opc = 0;

struct Traductor{
	int n;
	char espanol[20];
	char ingles[20];
	char funcion[1000];
};

void menu();
void crear();
void leer();
void actualizar();
void delete_line();
void readforiginal();
void diccionario();
void lecturaCodigo();

main(){
menu();
}

void menu(){
	system("cls");
	
cout<<"1. Ingresar Palabra y funcion"<<endl;
cout<<"2. Ver Palabras"<<endl;
cout<<"3. Actualizar Palabras"<<endl;
cout<<"4. Eliminar Palabras"<<endl;
cout<<"5. Ingresar codigo a traducir"<<endl;
cout<<"6. Salir"<<endl<<endl;
cout<<"Digite su opcion: ";
cin>>opc; 
			
	system("cls");
	
switch(opc)
	{
		case 1: crear();		 		;break;
 		case 2: leer();					;break;
 		case 3: actualizar();	 		;break;
 		case 4: delete_line();	 		;break;
 		case 5: lecturaCodigo();		;break;
 		case 6: exit(-1);				;break;  
		default:cout<<"Opcion no valida";  
	}	
}

void traducir(string codigol){
	/* ESTA FUNCION NO HACE NADA, A NO SER QUE SE QUIERA MANDAR A UN ARCHIVO LA TRADUCCION*/
	ofstream myfile ("codigoftrad.txt", ios::out | ios::app);
	  if (myfile.is_open())
	  {
	    myfile << codigol;
	    myfile.close();
	  }
	  else{
	   cout << "N/A traducir";
	  }
	  
}

void lecturaCodigo(){
	string linea="";


	cin.ignore();
	cout<<"______________________________________________________"<<endl;
	cout<<"####INGRESA LINEA A LINEA EL CODIGO A TRADUCIR####"<<endl;
	cout<<"______________________________________________________"<<endl;
	cout<<"Para empezar a traducir el codigo ingresa 'wq!' y este se traducira de forma automatica"<<endl<<endl;
	while(linea.compare("wq!")!=0){
		getline(cin,linea,'\n');
		if(linea.compare("wq!")!=0){
			traducir(linea);
			traducir("\n");
		}
	}
	cout<<"______________________________________________________"<<endl;

	readforiginal();
}

void diccionario(string line){
		string str = line;
		bool flag = false;
		FILE* archivo = fopen(nombre_archivo,"rb");	
		if (!archivo){
			archivo = fopen(nombre_archivo,"w+b");	
		}
		Traductor traductor;
		int id=0;	
		fread(&traductor,sizeof(Traductor),1,archivo);
		do{
		
					  
					  string str2 (string(traductor.ingles));
					  string nueva (string(traductor.espanol));
					  int tam = str2.length();
					  
					  size_t found = str.find(str2);
					  if (found!=string::npos){
					    //cout << "encontrado en " << found << '\n';
					    str.replace(found,tam,nueva);
					    //cout<<str<<endl;
					    flag = true;
					    //traducir(str);
					  }
		
		fread(&traductor,sizeof(Traductor),1,archivo);
		id+=1;	
		}while(feof(archivo)==0);
		if(flag ==true){
		cout<<str<<endl;	
		}
		if(flag ==false){
			cout<<line<<endl;
		}
		fclose(archivo);
	
}	

void readforiginal(){
		/*leer archivofuente*/
		int status;
		string line;
		cout<<"______________________________________________________"<<endl;
		cout<<"####TRADUCIENDO EL CODIGO####"<<endl;
		cout<<"______________________________________________________"<<endl;
	
		ifstream archivo ("codigoftrad.txt");
		//cout<<"/***************leyendo archivo fuente original*****************/"<<endl;
		
		if (archivo.is_open()){
			while(getline(archivo,line)){
			diccionario(line);		
			}
			
		    	archivo.close();
		}
		else{
		cout << "N/A readoriginal";	
		} 
		cout<<endl;
		status = remove("codigoftrad.txt");
   		 if(status==0){
			
   		cout<<"______________________________________________________"<<endl;
        cout<<"Hecho!"<<endl;
        cout<<"______________________________________________________"<<endl;
    	}
    		else{
    			cout<<"E/D!";
			}
        	
    	cout<<endl;
		system("pause");
		menu();
		
}


void leer(){
		system("cls");
		FILE* archivo = fopen(nombre_archivo,"rb");	
		if (!archivo){
			archivo = fopen(nombre_archivo,"w+b");	
		}
		Traductor traductor;
		int id=0;	
		fread(&traductor,sizeof(Traductor),1,archivo);
		cout<<"______________________________________________________"<<endl;
		cout<<"\t Listado de Palabras con su funcion"<<endl;
		do{
		cout<<"______________________________________________________"<<endl;
		cout<<"Id: "<<id<<endl;
		cout<<"No. "<<traductor.n<<endl;
		cout<<"Palabra en Ingles: "<<traductor.ingles<<endl;
		cout<<"Palabra en Espanol: "<<traductor.espanol<<endl;
		cout<<"Funcionalidad: "<<traductor.funcion<<endl;	
		fread(&traductor,sizeof(Traductor),1,archivo);
		id+=1;	
		}while(feof(archivo)==0);
		fclose(archivo);
		cout<<endl;
		
		//readforiginal();
		system("pause");
		menu();
}	
	
void actualizar(){
	FILE* archivo = fopen(nombre_archivo,"r+b");
	int id;
	Traductor traductor;
	string espanol,ingles,funcion;
	cout<<"Ingrese el Id que desea Modificar: ";
	cin>>id;
	fseek(archivo,id * sizeof(Traductor),SEEK_SET);
		cout<<"Ingrese el Numero: ";
		cin>>traductor.n;
		cin.ignore();
		cout<<"Ingrese la palabra en ingles: ";
		getline(cin,ingles);
		strcpy(traductor.ingles,ingles.c_str());
		cout<<"Ingrese la traduccion en espanol: ";
		getline(cin,espanol);
		strcpy(traductor.espanol,espanol.c_str());
		cout<<"Ingrese la funcionalidad: ";
		getline(cin,funcion);
		strcpy(traductor.funcion,funcion.c_str());
		cin.ignore();
	
	fwrite(&traductor,sizeof(Traductor),1,archivo);
	fclose(archivo);
	leer();
}	

void crear(){
	char continuar;
	FILE* archivo = fopen(nombre_archivo,"ab");
	Traductor traductor;
	string espanol,ingles,funcion;
	do{
		fflush(stdin);
		cout<<"Ingrese el Numero de palabra: ";
		cin>>traductor.n;
		cin.ignore();
		cout<<"Ingrese la palabra en ingles: ";
		getline(cin,ingles);
		strcpy(traductor.ingles,ingles.c_str());
		cout<<"Ingrese la palabra en espanol: ";
		getline(cin,espanol);
		strcpy(traductor.espanol,espanol.c_str());
		cout<<"Ingrese la funcion: ";
		getline(cin,funcion);
		strcpy(traductor.funcion,funcion.c_str());
		cin.ignore();
		fwrite(&traductor,sizeof(Traductor),1,archivo);
		cout<<"Dese Agregar otra palabra (s/n): ";
		cin>>continuar;
	} while ( (continuar=='s') || (continuar=='S') );
	fclose(archivo);
	leer();
}

void delete_line(){
 	
	FILE *archivo, *archivo_temp; 
	int n; 
	Traductor traductor; 
	
	archivo_temp=fopen(nombre_archivo_temp,"w+b"); 
	archivo=fopen(nombre_archivo,"rb"); 
	                      				                
	cout<<"No. de la palabra a eliminar:"<<endl; 
	cin>>n; 
	                                                                                
		while(fread(&traductor,sizeof(Traductor),1,archivo)){	
			if (traductor.n != n) 
			fwrite(&traductor,sizeof(Traductor),1,archivo_temp); 
			}
	                
		fclose(archivo_temp); 
		fclose(archivo); 
	                
		archivo_temp=fopen(nombre_archivo_temp,"rb"); 
		archivo=fopen(nombre_archivo,"wb"); 
	 
		while(fread(&traductor,sizeof(Traductor),1, archivo_temp)){ 
			fwrite(&traductor,sizeof(Traductor),1, archivo); 
		}
	                
	fclose(archivo_temp); 
	fclose(archivo); 
	
	leer(); 

}	

