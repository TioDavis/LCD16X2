#include <LiquidCrystal.h> //biblioteca do display

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //declara as portas utilizadas: RS=12, E(ou EN)=11, D4=5, D5=4, D6=3 e D7=2

//variáveis da rolagem de texto em linhas separadas
String l1 = "<<< Rolar linha 1 para a esquerda"; //mensagem linha 1
String l2 = "Rolar linha 2 para a direita >>>"; //mensagem linha 2
int ini, fim = 0; //variáveis para selecionar os caracteres da mensagem linha 1
int tam = l1.length(); //tamanho da mensagem linha 1
int pos1 = 16; //posição do cursor da linha 1
int pos2 = 0; //posição do cursor na linha 2
int tam2 = l2.length(); //tamanho da mensagem linha 2
int ini2 = tam2; //variáveis para selecionar os caracteres da mensagem linha 2
int fim2 = tam2;

//variáveis para cronômetro
int conti, seg, i, m = 0; //variáveis para contagem do tempo

void setup() {
  lcd.begin(16, 2); //inicializa o display e informa dimensão (colunas,linhas)
  pinMode(30, INPUT_PULLUP); //botão 1 (cronômetro) com o resistor PULLUP do Arduino ativado, botão deve ser conectado ao GND
  pinMode(32, INPUT_PULLUP); //botão 2 (rolar texto)
  pinMode(34, INPUT_PULLUP); //botão 3 (rolar linhas)
  pinMode(36, INPUT_PULLUP); //botão 4 (limpar tela)
  // put your setup code here, to run once:
}

void loop() {
  lcd.clear(); //limpa a tela
  lcd.print("PRESSIONE");
  lcd.setCursor(0, 1); //posicionar o cursor na coluna 0 e na linha 0
  lcd.print("QUALQUER TECLA"); //imprime mensagem no display
  if (digitalRead(30) == LOW) { //confere se B1 foi pressionado
    while (digitalRead(36) == HIGH) { //interrompe o cronômetro quando B4 for pressionado
      crono(); //chama a rotina do cronômetro
    }
    i = 0; //zera o cronômetro
  }
  if (digitalRead(32) == LOW) { //confere se B2 foi pressionado
    while (digitalRead(36) == HIGH) { //interrompe a rolagem no display
      scroll(); //chama a rotina para rolar mensagem no display
    }
  }
  if (digitalRead(34) == LOW) { //confere se B3 foi pressionado
    while (digitalRead(36) == HIGH) { //interrompe a rolagem de linhas no display
      scrolli(); //chama a rotina para rolar linhas
    }
  }
  if (digitalRead(36) == LOW) { //confere se B4 foi pressionado
    lcd.clear(); //limpa o display para imprimir nova mensagem
    lcd.print("Vamos recomecar?"); //imprime nova mensagem
    delay(500);
  }
  delay(500);
  // put your main code here, to run repeatedly:
}

void scroll() { //rolar texto completo no display para a direita e esquerda com potenciômetro
  lcd.clear(); //limpa o display
  lcd.print("  Rolar texto"); //mensagem impressa na primeira linha
  delay(750); //aguarda 0,75s
  lcd.clear(); //limpa o display novamente para imprimir uma nova mensagem
  lcd.print(">>> Direita >>>"); //mensagem exibida no display
  lcd.setCursor(0, 1); //posiciona o cursor na segunda linha (1) e primeira coluna (0), não é necessário setar na primeira linha, a menos que precise trocar a coluna
  lcd.print(" -> -> -> -> -> ");
  delay(500);
  for (int pos = 0; pos < 16; pos++) { //rotina para deslocar o texto para a direita
    lcd.scrollDisplayRight(); //rola o texto um passo para a direita
    delay(150);
  }
  lcd.clear();
  lcd.print("<<< Esquerda <<<");
  lcd.setCursor(0, 1);
  lcd.print(" <- <- <- <- <- ");
  delay(500);
  for (int pos = 0; pos > -16; pos--) { //rotina para descolar o texto para a esquerda
    lcd.scrollDisplayLeft(); //rola o texto um passo para a esquerda
    delay(150);
  }
}

void crono() { //cronômetro
  if (i == 0) { //condição para configurar o valor inicial do contador de segundos
    conti = millis() / 1000; //define o valor inicial do contador
    i++; //variável de controle do contador inicial
  }
  seg = (millis() / 1000) - conti; //contador de segundos
  if (seg > 59) { //condição para zerar os segundos
    m++;//variável de minutos
    i = 0;
    seg = 0;
  }
  if (m > 59) { //condição para zerar os minutos
    m = 0;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cronometro");
  lcd.setCursor(0, 1);
  if (m < 10) {
    lcd.print("0");
    lcd.print(m);
  }
  else {
    lcd.print(m);//imprime o valor em minutos
  }
  lcd.print(":");
  if (seg < 10) {
    lcd.print("0");
    lcd.print(seg);
  }
  else {
    lcd.print(seg); //imprime o valor em segundos
  }
  delay(250);
}

void scrolli() { //rolar linhas separadamente
  lcd.clear();
  lcd.setCursor(pos1, 0); //posiciona o cursor da linha 1 na coluna pos1
  lcd.print(l1.substring(ini, fim)); //funciona como se fosse um vetor, quebra a mensagem l1 e coloca cada caracter em uma posição. Os valores entre o intervalo ini e fim são apresentados no display, sendo ini o primeiro caracter e fim o último
  lcd.setCursor(pos2, 1); //posiciona o cursor da linha 2 na coluna pos2
  lcd.print(l2.substring(ini2, fim2)); //estrutura a mensagem em l2 em um vetor e apresenta os caracteres entre os intervalos ini2 e fim2
  //deslocar linha 1 para a esquerda
  if (ini == 0 && pos1 > 0) { //confere se o primeiro caracter ainda é visível
    pos1--; //desloca o cursor (e a frase em l1)para a esquerda
    fim++; //revela mais uma letra da frase em l1
  }
  else if (ini == fim) { //confere se todos os caracteres já foram apresentados e reseta as variáveis
    ini = fim = 0; //intervalo retorna à zero
    pos1 = 16; //cursor retorna à posição final do display
  }
  else if (fim == tam && pos1 == 0) { //confere se ainda há caracteres a serem exibidos
    ini++; //desloca o caracter inicial para a direita
  }
  else { //caso ainda exista caracteres em exibição (ini e fim não chegaram nos limites) e o cursor chegou na posição 0, segue descolando a mensagem para a esquerda
    ini++; //desloca o caracter inicial para a direita
    fim++; //revela mais um caracter em l1
  }
  //desloca linha 2 para a direita
  if ((fim2 - ini2) < 16 && pos2 == 0) { //confere se o cursor está na posição 0 e quanto da mensagem em l2 foi apresentada
    ini2--; //desloca o caracter inicial para a esquerda
  }
  else if (ini2 == fim2) { //confere se todos os caracteres foram apresentados e reseta os parâmetros
    ini2 = fim2 = tam2; //retornam os valores ini2 e fim2 para o ponto máximo de l2
    pos2 = 0; //retorna o cursor para a posição 0 do display
  }
  else if (ini2 == 0 && pos2 < 16) { //confere se ainda há caracteres a serem apresentados de l2
    fim2--; //desloca o último caracter de l2 para a esquerda
    pos2++; //desloca o cursor (e a frase l2) para a direita
  }
  else { //caso ainda existam caracteres em exibição (ini2 e fim2 ainda não chegaram nos limites) e o cursor chegou na posição 16, segue deslocando a mensagem para a direita
    ini2--; //desloca o caracter inicial para a esquerda
    fim2--; //desloca o caracter final para a esquerda
  }
  delay(500);
}
