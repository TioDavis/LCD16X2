<h1>LCD16X2 com Arduino</h1>
<h3>Introdução</h3>
<p align=justify>Este projeto apenas demonstra algumas funcionalidades do LCD com Arduino. Para ser mais direto, são apresentados 4 exemplos: como exibir uma menagem no display 16x2 que atualiza o valor em tempo real, deslocar o texto para os lados, deslocar uma linha específica e limpar a tela para mostrar uma nova mensagem.</p>
<h4>Materiais</h4>
<p><li>1 Arduino Mega</li>
  <li>1 LCD 16x2</li>
  <li>4 push buttons</li>
  <li>1 protoboard</li>
  <li>1 potenciômetro de 10kΩ</li>
  <li>Fios jumpers</li></p>
  <h3>Display de Cristal Líquido</h3>
  <p align=justify>O LCD, como o próprio nome já informa, é uma interface gráfica que utiliza o cristal líquido entre duas placas de vidro, em conjunto de um backligth e um controlador matricial para os pixels da tela, para formar imagens. O cristal líquido é um estado físico da matéria, também conhecido como mesofase, cujo as substâncias apresentam as propriedades físicas de sólidos e líquidos. O campo elétrico aplicado sobre o cristal líquido alterna o seu comportamento, o tornando transparente ou opaco. Esta é a base da construção e funcionamento do LCD.</p>
  <h3>LCD 16x2</h3>
  <p align=justify>O LCD 16x2 é um módulo de interface gráfica que permite a visualização de textos e símbolos, encontrado nas cores verde ou azul. Possui 16 pinos para conexão, 16 colunas e 2 linhas na tela. É ideal para projetos compactos e que apresentam pouca informação ao usuário. Permite comunicação serial, por meio de uma interface I2C, ou paralela, diretamente em seu barramento.</p>
  <p><b>Pinos LCD 16x2</b></p>
<table>
  <tr align=center><td>VSS</td><td>Alimentação 0V (GND)</td></tr>
  <tr align=center><td>VDD</td><td>Alimentação 5V (VCC)</td></tr>
  <tr align=center><td>VO</td><td>Contraste do LCD</td></tr>
  <tr align=center><td>RS</td><td>Seleção de comandos (0) ou dados (1)</td></tr>
  <tr align=center><td>R/W</td><td>Leitura (1) e escrita (0)</td></tr>
  <tr align=center><td>E</td><td>Ativa (1) / desativa (0) o display (Enable)</td></tr>
  <tr align=center><td>DB4</td><td>Data bit 4</td></tr>
  <tr align=center><td>DB5</td><td>Data bit 5</td></tr>
  <tr align=center><td>DB6</td><td>Data bit 6</td></tr>
  <tr align=center><td>DB7</td><td>Data bit 7</td></tr>
  <tr align=center><td>A</td><td>Anodo da iluminação (5V)</td></tr>
  <tr align=center><td>K</td><td>Catodo da iluminação (GND)</td></tr>
</table>
<p align=justify>A comunicação serial necessita de apenas 4 pinos: <b>GND, VCC, SDA e SCL</b>. Já a comunicação serial exige mais portas: <b>RS, R/W, E (pinos de controle), VDD, VSS (alimentação do módulo), A, K (alimentação do backlight), VO (controle do contraste), DB4, DB5, DB6 e DB7 (bits de entrada)</b>.</p>
<h3>O Projeto</h3>
<p align=justify>O objetivo deste projeto é demonstrar alguns recursos que podem ser utilizados no display LCD 16x2. A primeira mensagem impressa no display solicita que uma tecla seja pressionada. São 4 botões e cada um resulta em uma ação diferente.
  <li align=justify><b>Botão 1:</b> inicia um cronômetro digital de 60 minutos, ou seja, zera após completar uma hora. Ele pode ser interrompido a qualquer momento quando acionado o botão 4.</li>
  <li><b>Botão 2:</b> chama a função scroll que permite rolar o texto para os lados. Uma mensagem é apresentada e em seguida a mensagem é deslocada para a direita e depois para a esquerda. Pressionar o botão 4 para a rotina.</li>
  <li><b>Botão 3:</b> outra função de rolagem de texto, no entanto há uma diferença: na rotina anterior todo o conteúdo do display rolava para os lados em conjunto, nesta as linhas rolam para lados opostos independentes uma da outra. Ou seja, enquanto a linha de cima rola para a esquerda, a linha de baixo rola para a direita. O processo para quando o botão 4 é pressionado.</li>
  <li><b>Botão 4:</b> botão de reset. Para qualquer mensagem que esteja sendo apresentada no display e retorna à mensagem inicial.</li>
<br>Vale ressaltar que o Arduino Mega possui resistores de pullup, assim dispensa o uso de resistores em conjunto com os push buttons. Neste caso os pinos digitais estão em nível lógico alto e os botões devem ser conectados ao GND. Quando acionados os pinos vão para nível lógico baixo.</p>
<p><b>Circuito do Projeto</b></p>
<img src="Circuito Display.JPG">
