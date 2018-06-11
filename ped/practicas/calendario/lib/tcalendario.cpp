//Raimundo Fenoll Albaladejo
#include "tcalendario.h"
#include "string.h"

//Constructor por defecto
TCalendario::TCalendario() {
  
  dia=1;
  mes=1;
  anyo=1900;
  mensaje=NULL;
}

//Constructor que inicializa calendario con parámetros pasados
TCalendario::TCalendario(const int d, const int m, const int a, const char * mens) {
  
  if(esCorrecto(d,m,a)) {
    dia=d;
    mes=m;
    anyo=a;
    
    //mensaje=mens. ERROR, estamos asignando dos punteros a la misma posicion de memoria y no copiando los mesajes.
    if(mens!=NULL) {
      mensaje = new char[strlen(mens)+1]; //Asigno la misma capacidad de memoria a mens que a mensaje
      strcpy(mensaje, mens); // Copio el mensaje
      
    }
    else {
      mensaje=NULL;
      
    }
    
  }
  
  else {
    dia=1;
    mes=1;
    anyo=1900;
    mensaje=NULL;
  }
}
  
//Constructor de Copia
TCalendario::TCalendario(const TCalendario &c) {
  
  dia=c.dia;
  mes=c.mes;
  anyo=c.anyo;
  
  //mensaje=c.mensaje. ERROR, estamos asignando dos punteros a la misma posicion de memoria y no copiando los mesajes.
    
  if(c.mensaje!=NULL) {
    mensaje = new char[strlen(c.mensaje)+1]; //Asigno la misma capacidad de memoria a mens que a mensaje
    strcpy(mensaje, c.mensaje); // Copio el mensaje
    
  }
  
  else {
    mensaje=NULL;
  }
}

//Destructor
TCalendario::~TCalendario() {
  
  dia=1;
  mes=1;
  anyo=1990;
  if(mensaje!=NULL) {
    delete[] mensaje; //Mensaje es un puntero, y con esto lo que hacemos es liberar la memoria del objeto al que apunta(el destructor no puede hacer esto)
    mensaje=NULL;
    
  }
  
  else {
    mensaje=NULL;
  }
}

//Sobrecarga del operador asignación
TCalendario &TCalendario::operator=(const TCalendario &c) { 
  
  if(this != &c) {
    
    (*this).~TCalendario(); //Borramos el contenido de nuestro objeto TCalendario.
    
    dia=c.dia;
    mes=c.mes;
    anyo=c.anyo;
    
    //Mensaje ya está a NULL porque hemos llamado al destructor
    
    if(c.mensaje!=NULL) { //Comprobemos si c.mensaje no es nulo
      mensaje = new char[strlen(c.mensaje)+1]; //Asigno la misma capacidad de memoria a mens que a mensaje
      strcpy(mensaje, c.mensaje); // Copio el mensaje
    }
    
  }
  
  return *this;
}

//EsVacio
bool TCalendario::EsVacio() {
  
	bool ok = false;
  
  if(dia==1 && mes==1 && anyo==1900 && mensaje==NULL) {
    ok=true;
  }
  
  return ok;
}

//Fecha Correcta
bool TCalendario::esCorrecto(int dia, int mes, int anyo) {
  
  bool date=false;
  
  if(dia<1 || dia>31 || mes<1 ||mes>12 || anyo<1900) { //Error si se pasa de los límites
    date=false;
  }
  
  else {
    
    if(Mes_par(mes) && (dia<=30)) { //Meses con 30 días
      date=true;
    }
    
    else if(Mes_impar(mes) && (dia<=31)) { //Meses con 31 días
      date=true;
    }
    
    else if(mes==2) { //Febrero
      if((esBisiesto(anyo)==true) && (dia<=29)) { //Si es febrero y bisiesto, 29 días o menos
	  date=true;
      }
      else {
	if(dia<=28) { //Si es febrero y no bisiesto, 28 días o menos
	  date=true;
	}
      }
    }
  }
  
  return date; 
}

//Año Bisiesto
bool TCalendario::esBisiesto(int anyo) {
  
  bool bisiesto=false;
  if((anyo%4==0) && (anyo%400==0 || anyo%100!=0)) {
    bisiesto=true;
  }
  
  return bisiesto; 
}

//Modificamos la fecha
bool TCalendario::ModFecha(const int dia, const int mes, const int anyo) {
  
  bool mod;
  
  if(esCorrecto(dia,mes,anyo)==true) {
    this->dia=dia;
    this->mes=mes;
    this->anyo=anyo;
    
    mod=true;
    
  }
  
  else {
    mod=false;
  }
  
  return mod;
  
}

//Modificamos el mensaje
bool TCalendario::ModMensaje(const char * mens) {
  
  bool mod;
 
  if(mens!=NULL) {
    mensaje = new char[strlen(mens)+1]; //Asigno la misma capacidad de memoria a mens que a mensaje
    strcpy(mensaje, mens); // Copio el mensaje
    mod=true;
    
  }
  
  else {
    mensaje=NULL;
    mod=true;
  }
  
  return mod;
}

//Se sobrecarga el operador << (Cuando hagas <<TCalendario se llamará a este método)
ostream & operator<<(ostream &os, const TCalendario &c) {
  
    if(c.dia<10 && c.mes<10) {
      if(c.mensaje==NULL) {
			os<<0<<c.dia<<"/"<<0<<c.mes<<"/"<<c.anyo<<" "<<"\""<<"\"";
      }

		  else {
			os<<0<<c.dia<<"/"<<0<<c.mes<<"/"<<c.anyo<<" "<<"\""<<c.mensaje<<"\"";
		  }
			
    }
    
    else if(c.dia<10) {
		  if(c.mensaje==NULL) {
			os<<0<<c.dia<<"/"<<c.mes<<"/"<<c.anyo<<" "<<"\""<<"\"";
		  }
		  else {
			os<<0<<c.dia<<"/"<<c.mes<<"/"<<c.anyo<<" "<<"\""<<c.mensaje<<"\"";
		  }
      
    }

    else if(c.mes<10) {
		  if(c.mensaje==NULL) {
			os<<c.dia<<"/"<<0<<c.mes<<"/"<<c.anyo<<" "<<"\""<<"\"";
		  }
		  else {
			os<<c.dia<<"/"<<0<<c.mes<<"/"<<c.anyo<<" "<<"\""<<c.mensaje<<"\"";
		  }    
    }

    else {
		  if(c.mensaje==NULL) {
			os<<c.dia<<"/"<<c.mes<<"/"<<c.anyo<<" "<<"\""<<"\"";
		  }
		  else {
			os<<c.dia<<"/"<<c.mes<<"/"<<c.anyo<<" "<<"\""<<c.mensaje<<"\"";
		  }
	 } 
   return os;
}

//Suma días
TCalendario TCalendario::operator+(const int day) {

  TCalendario add(*this);
  
  add.dia=dia+day;
  
  while(!esCorrecto(add.dia, add.mes, add.anyo)) {
    
    if(add.mes==12) { //Habrá que sumar el año cuando sea Diciembre
      add.dia=add.dia-31;
      add.mes=1;
      add.anyo++;
    }
    
    else if(Mes_impar(add.mes)) { //Si el siguente mes tiene 31 días
      add.dia=add.dia-31;
      add.mes++;	
    }
    
    else if(Mes_par(add.mes)) { //Si el siguiente mes tiene 30 días
      add.dia=add.dia-30;
      add.mes++;
    }
      
    else if(add.mes==2 && esBisiesto(add.anyo)) { //Si el siguiente mes es febrero y bisiesto
      add.dia-29;
      add.mes++;
    }
      
    else if(add.mes==2 && !esBisiesto(add.anyo)) { //Si el siguente mes es febrero y no es bisiesto
      add.dia=add.dia-28;
      add.mes++;	
    }
   
  }
  
  return add;
}

//Resta días
TCalendario TCalendario::operator-(const int day) {
  
  bool date=false;
  TCalendario sub(*this);
  
  sub.dia=dia-day;
  
  while(!esCorrecto(sub.dia, sub.mes, sub.anyo) && date==false) {
    
    if(sub.anyo<1900) {
      date=true;
      
      sub.dia=1;
      sub.mes=1;
      sub.anyo=1900;
      sub.mensaje=NULL;
    }
    
    else if(sub.mes==1) { //Habrá que sumar el año cuando sea Diciembre
      sub.dia=sub.dia+31;
      sub.mes=12;
      sub.anyo--;
    }
    
    else if(Mes_impar(sub.mes)) { //Si el siguente mes tiene 31 días
      sub.dia=sub.dia+31;
      sub.mes--;	
    }
    
    else if(Mes_par(sub.mes)) { //Si el siguiente mes tiene 30 días
      sub.dia=sub.dia+30;
      sub.mes--;
    }
      
    else if(sub.mes==2 && esBisiesto(sub.anyo)) { //Si el siguiente mes es febrero y bisiesto
      sub.dia+29;
      sub.mes--;
    }
      
    else if(sub.mes==2 && !esBisiesto(sub.anyo)) { //Si el siguente mes es febrero y no es bisiesto
      sub.dia=sub.dia+28;
      sub.mes--;	
    }
   
  }
  
  return sub;
}

//PostIncremento
TCalendario TCalendario::operator++(const int day) {
  
  TCalendario c(*this); //Copiamos el contenido del objeto
  
  //Se aplica sobre el propio calendario
  dia=dia+1;
  
  while(!esCorrecto(dia,mes,anyo)) {
    
    if(mes==12 && dia==32) {
      dia=1;
      mes=1;
      anyo=anyo+1;
    }
    
    else if(Mes_impar(mes) && dia==32) {
      dia=1;
      mes=mes+1;
    }
    
    else if(Mes_par(mes) && dia==31) {
      dia=1;
      mes=mes+1;
    }
    else if(mes==2 && esBisiesto(anyo) && dia==30) {
      dia=1;
      mes=3;
    }
    else if (mes==2 && !esBisiesto(anyo) && dia==29) {
      dia=1;
      mes=3;
    }
  }
  
  return c;
}

//PreIncremento
TCalendario &TCalendario::operator++(void) {
  
  dia=dia+1;
  
  while(!esCorrecto(dia,mes,anyo)) {
    
    if(mes==12 && dia==32) {
      dia=1;
      mes=1;
      anyo=anyo+1;
    }
    
    else if(Mes_impar(mes) && dia==32) {
      dia=1;
      mes=mes+1;
    }
    
    else if(Mes_par(mes) && dia==31) {
      dia=1;
      mes=mes+1;
    }
    
    else if(mes==2 && esBisiesto(anyo) && dia==30) {
      dia=1;
      mes=3;
    }
    
    else if (mes==2 && !esBisiesto(anyo) && dia==29) {
      dia=1;
      mes=3;
    }
  }
  
  return *this;
}

//PostDecremento
TCalendario TCalendario::operator--(const int day) {
  
  TCalendario c(*this); //Copiamos el contenido del objeto
  
  bool date=false;
  //Se aplica sobre el propio calendario
  dia=dia-1;
  
  while(!esCorrecto(dia,mes,anyo) && !date) {
    
    if(anyo<1900) {
	  date=true;
      
      dia=1;
      mes=1;
      anyo=1900;
      mensaje=NULL;
	}
	
    else if(mes==1 && dia==1) {
      dia=31;
      mes=12;
      anyo=anyo-1;
    }  
    else if((mes==5 || mes==7 || mes==10 || mes==12) && dia==1) {
      dia=30;
      mes=mes-1;
    }
    else if((mes==1 || mes==2 || mes==4 || mes==6 || mes==8 || mes==9 || mes==11) && dia==1) {
      dia=31;
      mes=mes-1;
    }
    else if(mes==3 && esBisiesto(anyo) && dia==1) {
      dia=29;
      mes=2;
    }
    else if(mes==3 && esBisiesto(anyo) && dia==1) {
      dia=28;
      mes=2;
    }
    
  }
  
  return c;
}

//PreDecremento
TCalendario &TCalendario::operator--(void) {
  
  bool date=false;
  //Se aplica sobre el propio calendario
  dia=dia-1;
  
  while(!esCorrecto(dia,mes,anyo) && !date) {
    
    if(anyo<1900) {
	  date=true;
      
      dia=1;
      mes=1;
      anyo=1900;
      mensaje=NULL;
	}
		
    else if(mes==1 && dia==0) {
      dia=31;
      mes=12;
      anyo=anyo-1;
    }  
    else if((mes==5 || mes==7 || mes==10 || mes==12) && dia==0) {
      dia=30;
      mes=mes-1;
    }
    else if((mes==2 || mes==4 || mes==6 || mes==8 || mes==9 || mes==11) && dia==0) {
      dia=31;
      mes=mes-1;
    }
    else if(mes==3 && esBisiesto(anyo) && dia==0) {
      dia=29;
      mes=2;
    }
    else if(mes==3 && esBisiesto(anyo) && dia==0) {
      dia=28;
      mes=2;
    }
    
  }
  
  return *this; 
}

//Igualdad de Calendarios
bool TCalendario::operator==(const TCalendario &c) {
  
  bool ok = false;
  bool equal = true;

  if(this != &c) {
  
    //Entra cuando solo difieran en la fecha
    if(dia==c.dia && mes==c.mes && anyo==c.anyo) {

      //Los dos mensajes null
      if(mensaje == NULL && c.mensaje == NULL) {

          ok=true;
      }

      else {

        //Los dos mensajes tienen algo
        if(c.mensaje != NULL && mensaje != NULL) {

          //No tienen la misma longitud
          if(strlen(mensaje) != strlen(c.mensaje)) {

            //cout << "distina longitud"<<endl;
            ok = false;
          }

          else {
          
            for(unsigned int i=0; i<strlen(c.mensaje) && equal; i++) {
          
              if(mensaje[i] != c.mensaje[i]) {

                cout<<"entra"<<endl;
                equal = false;
              }
            }

            if(equal) {
              ok = true;
            }

            else {
              ok = false;
            }
          }
        }
      }
    }
  }

  return ok;
}

//Desigualdad de Calendarios
bool TCalendario::operator!=(const TCalendario &c) {
  
  bool ok=false;
  
  if(dia!=c.dia || mes!=c.mes || anyo!=c.anyo) {
    ok=true;
  }

  else {
    if(mensaje==NULL) {
      if(c.mensaje==NULL) {
        ok=true;
      }
    }

    else {
      if(c.mensaje==NULL) {
        ok=true;
      }

      else {
        int j=0;

        if(j!=strcmp(mensaje,c.mensaje)) {
          ok=true;
        }
      }
    }
  }
  return ok;
}

//Mayor Que
bool TCalendario::operator>(const TCalendario &c) {
  
  bool ok=false;
  
  if(anyo>c.anyo) {
    ok=true;
  }
  if(anyo==c.anyo && mes>c.mes) {
    ok=true;
  }
  if(anyo==c.anyo && mes==c.mes && dia>c.dia) {
    ok=true;
  }
  return ok;
}

//Menor Que
bool TCalendario::operator<(const TCalendario &c) {
  
  bool ok=false;
  
  if(anyo<c.anyo) {
    ok=true;
  }
  if(anyo==c.anyo && anyo<c.anyo) {
    ok=true;
  }
  if(anyo==c.anyo && mes==c.mes && dia<c.dia) {
    ok=true;
  }
  return ok;
}

//meses con 31 Días
bool TCalendario::Mes_impar(int mes) {
  
  bool ok=false; 
  if(mes==1||mes==3||mes==5||mes==7||mes==8||mes==10||mes==12) {
    ok=true;
  }
  return ok;
}

//Meses con 30 Días
bool TCalendario::Mes_par(int mes) {
  
  bool ok=false;
  if(mes==4||mes==6||mes==9||mes==11) {
    ok=true;
  }
  return ok;
}


  
  


    











    









    
    
    

    
  
  
  
  
    
  
  
  
  
  




  
  
