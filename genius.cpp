unsigned short int coresGeradas[800];//cores geradas "aleatoriamente"
enum State_enum {MOSTRAR_NUMEROS, JOGADA, PERDEU};//maquina de estados
uint8_t state = MOSTRAR_NUMEROS;//define primeiro estado
int i = 0, u=0;
bool stateButton[4];
unsigned short int atCor;
const int la = 222.02, perdeu = 66;
#define TEMPO  500
int buzzer = 11;

void setup() {
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(buzzer,OUTPUT);
  for(int i = 0; i<100;i++){
    coresGeradas[i] = 0;
  }
}

void loop() {  
  
  switch(state)
  {
    case MOSTRAR_NUMEROS:
      MostrarNumeros();
      state = JOGADA;
      break;
       
    case JOGADA:
      Jogada();
      break;
    case PERDEU:
      Perdeu();
      state = MOSTRAR_NUMEROS;
      break;
  }
}

void MostrarNumeros(){
  int x = 0;
  atCor = random(4);
  coresGeradas[u] = (atCor << (i << 1)) + coresGeradas[u];//gera cores aleatorias
  for(int j = 0; j <= i+u*8; j++){//mostra todas cores aleatorias ate o momento
    if(j%8 == 0 && j!=0)
      x++;
    digitalWrite(pegaAtual(x,j%8)+3,HIGH);
    toque(buzzer, la*(pegaAtual(x,j%8)+1),1-float(i+u*8)/6400.);
    digitalWrite((pegaAtual(x,j%8) )+3,LOW);
    delay(100);
  }
  i++;
  if(i == 8){
    i= 0 ;
    u++;
  }
}

void Jogada(){//lembrar que eu tenho que ter em mente que aqui eh i+1
  for(int k = 0 ; k < 4 ; k++)
    stateButton[k] = 0;
  int jaDigitado = 0;
  int x = 0;
  for(int k = 0 ; k < i+u*8; k++){//i na vdd é i+1
    if (k%8 == 0 && k!=0)
      x++;
    atCor = -1;
    while(atCor == -1){
      for(int j = 0; j<4; j++){
        stateButton[j] = digitalRead(j+7);
        if(stateButton[j] != 0){
          atCor = j;
        }
      }
    }
    int tempo = millis();
    digitalWrite(atCor+3,HIGH);
    while(stateButton[atCor] != 0 || tempo - millis() < 100){
      tone(buzzer,la*(atCor+1));
      stateButton[atCor] = digitalRead(atCor + 7);
    }
    digitalWrite(atCor+3,LOW);
    noTone(buzzer);
    for(int b = 0; b <4; b++)
      stateButton[b] = 0;
    
   if(atCor == pegaAtual(x,k%8)){
          state = MOSTRAR_NUMEROS;
    }
    
    if(atCor != pegaAtual(x,k%8)){
          state = PERDEU;
          break;
    } 
  }
  delay(500);
}

void Perdeu(){
  float si = 249.22, fa = 176.22,mi = 166.32,re = 148.1,notaDo = 132;
  for(int k = 0; k<100 ; k++){
    coresGeradas[k] = 0;
  }
  i = 0;
  u = 0;
  atCor = 0;
  digitalWrite(3,HIGH);
  toque(buzzer, la,0.2);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(3,HIGH);
  toque(buzzer, fa*2,0.2);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(3,HIGH);
  toque(buzzer, fa*2,0.2);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(3,HIGH);
  toque(buzzer, fa*2,0.2);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(3,HIGH);
  toque(buzzer, mi*2,0.2);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(3,HIGH);
  toque(buzzer, re*2,0.2);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(3,HIGH);
  toque(buzzer, notaDo*2,0.2);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(3,HIGH);
  toque(buzzer, mi,0.2);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(3,HIGH);
  toque(buzzer, re,0.2);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(3,HIGH);
  toque(buzzer, notaDo,0.3);
  digitalWrite(3,LOW);
  delay(100);
  
  delay(2000);
}

void toque(int buzzer,int nota, float t){
  tone(buzzer,nota);
  delay(float(TEMPO*t));
  noTone(buzzer);
}

unsigned short int pegaAtual(int u, int j){
  unsigned short int atual, A, B;
  A = ((coresGeradas[u]>>2*(j+1))<<2*(j+1));
  B = coresGeradas[u]%(int(pow(4,j))+1);
  if(j == 0)
    B = 0;
  atual = coresGeradas[u] - A - B;
  atual = atual >> j*2;
  return atual;
}
