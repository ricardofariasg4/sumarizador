<h1>Sumarizador de dados de GPS</h1>

<p>Atualmente, a maioria dos ciclocomputadores utilizados pelos ciclistas (amadores e profissionais) possuem um GPS. Esses dispositivos também conversam com diferentes sensores, como por exemplo, sensor de frequência cardíaca, velocidade, cadência, potência, etc. Isso permite que o ciclista/treinador possa analisar os dados do pedal e verificar se o treino foi realizado conforme prescrito.</p>

<p>Todas essas informações (GPS e sensores) são armazenadas a cada segundo. No exemplo abaixo, temos o log de dois segundos. As duas primeiras linhas contém a informação da bicicleta utilizada e a data da atividade. Na sequência, temos diversos campos com os respectivos valores e unidades registrados a cada segundo. Note que nem todos os campos estarão disponíveis. Por exemplo, se o ciclista não usar um sensor de frequência cardíaca, o campo heart_rate não existirá.</p>

<pre class="code">Gear: Cannondale SuperSix
Date: Nov 2, 2020, 10:26:44 AM

altitude: 973.8 m
ascent: 0 m
battery_soc: 100.0 percent
cadence: 62 rpm
calories: 0 kcal
distance: 2.21 m
enhanced_altitude: 973.8 m
enhanced_speed: 3.343 m/s
gps_accuracy: 2 m
grade: 7.9 %
heart_rate: 112 bpm
left_pedal_smoothness: 30.0 percent
left_right_balance: 56
left_torque_effectiveness: 95.0 percent
position_lat: -302650798 semicircles
position_long: -587443105 semicircles
power: 201 watts
right_pedal_smoothness: 28.0 percent
right_torque_effectiveness: 85.5 percent
speed: 3.343 m/s
timestamp: 2020-11-02 10:26:45

altitude: 973.8 m
ascent: 0 m
battery_soc: 100.0 percent
cadence: 63 rpm
calories: 0 kcal
distance: 5.18 m
enhanced_altitude: 973.8 m
enhanced_speed: 3.312 m/s
gps_accuracy: 2 m
grade: 7.2 %
heart_rate: 112 bpm
left_pedal_smoothness: 30.5 percent
left_right_balance: 55
left_torque_effectiveness: 95.0 percent
position_lat: -302650524 semicircles
position_long: -587442916 semicircles
power: 194 watts
right_pedal_smoothness: 28.0 percent
right_torque_effectiveness: 85.5 percent
speed: 3.312 m/s
timestamp: 2020-11-02 10:26:46</pre>

<p>O programa deverá apresentar as seguintes opções ao usuário:</p>
<ul>
  <li>Bicicletas Encontradas: Mostra todas as bicicletas encontradas durante o processamento dos arquivos de log.</li>
  <li>Pede para o usuário informar uma das bicicletas encontradas e apresenta a lista de atividades, resumo conforme descrito acima.</li>
  <li>Lista todas atividades agrupadas por bicicleta e ordenadas pela data</li>
  <li>Lista todas atividades agrupadas por bicicleta e ordenadas pela distância</li>
  <li>Lista todas atividades ordenadas pela subida acumulada</li>
  <li>Histograma: O usuário deve escolher uma bicicleta e apresentar um histograma da seguinte forma:
  O histograma deve mostrar a distribuição da distância das atividades da bicicleta escolhida como no exemplo abaixo. Para facilitar a comparação, o    gráfico deve conter um número fixo de colunas no qual cada coluna contém os intervalos de 10km. Para definir o número de colunas, você deve encontrar a atividade mais curta (C) e a mais longa (L). Por exemplo, suponha C = 25 e L = 124. Nesse caso, a primeira linha do histograma vai de 20 a 29, a segunda de 30 a 39 e assim por diante sendo que a última linha deve conter a atividade mais longa. O histograma pode ser apresentado no formato ASCII como no exemplo abaixo, com as distâncias no eixo y e a quantidade de atividades no eixo x:</li>
<img src="https://wiki.inf.ufpr.br/maziero/lib/exe/fetch.php?w=450&tok=9a4c5b&media=prog2:histogramaascii.png"></img>

<h2>Funcionamento</h2>
<p>O programa lê vários dados de logs de GPS de um determinado diretório, especificado na chamada do programa, com isso, realiza a sumarização dos dados</p>

<h2>Compilação</h2>
<p>Antes de iniciar o processo de compilação, siga as estapas abaixo:</p>
<p>1 - Esteja em ambiente linux (derivado de debian)<br><br>
2 - Instale os itens necessários para compilação com o seguinte comando:<br>
<code>sudo apt install gcc g++ make</code><br><br>
3 - Por fim, para compilar, estando na raiz do projeto, execute:<br>
<code>make</code></p>

<h2>Uso</h2>
<p>Se os passos acima foram bem sucedidos, estando na raiz do projeto basta executar o seguinte:<br>
<code>./gps -d {diretório de arquivos log}</code><br><br>
<b>Observação:</b> Se deseja passar o diretório logs que esteja localizado em sua home, faria: ~/logs ou /home/usuario/logs<br>
no entanto, para que o programa leia corretamente, é necessário inserir uma barra final, para indicar que se trata de um diretório, dessa forma, você
deve passar: ~/logs/ ou /home/usuario/logs/
</p>

  <h2>Arquivos para teste</h2>
Link para arquivos de log que podem ser usados para teste: 
  <a href="https://www.inf.ufpr.br/lesoliveira/ci1002/log2.tar.gz">Arquivos LOG</a>
