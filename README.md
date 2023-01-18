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
<code>./gps -d {diretório de arquivos log}</code>
</p>

  <h2>Arquivos para teste</h2>
Link para arquivos de log que podem ser usados para teste: 
  <a href="https://www.inf.ufpr.br/lesoliveira/ci1002/log2.tar.gz">Arquivos LOG</a>
