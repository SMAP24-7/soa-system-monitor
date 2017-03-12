#System Monitor

##Compilación

<p> Para compilar solo hay que seguir los siguientes pasos</p>

<ul>
	<li>Descargalo desde [github] (https://github.com/SMAP24-7/soa-system-monitor)</li>
	<li>Añade este proyecto a Qt Community 5.8 como nuevo proyecto</li>
	<li>Compila el programa</li>
	<li>Saldrá un cuadro de diálogo con tres pestañas
	<ol>
		<li>  <em> Hwmon</em> : Recopila informaicón de los sensores del sietema</li>
		<li><em>Procesos</em>: Muestra una lista con todos los procesos abiertos</li>
		<li><em>Hardware</em>: Muestras los especificaciones físicas del equipo</li>
		</li> </ol>
</ul>

##Características

<ul>
<li>Está compilado con un procesador de 64-bits, por lo que podría dar problemas en otro tipo de procesadores</li>
<li>Al pulsar en cada pestaña, esta crea un hilo para ejecutar la tarea y así no ralentizar el programa principal</li>
<ol>
<li><em>Hwmon</em>: Usamos un Thread bajo señales de la clase principal</li>
<li><em>Procesos</em>: Usa un pool de hilos gestionados por Qt</li>
<li><em>Hardware</em>: Usa un Thread bajo señales</li>
</ol></ul>

##Concurrencia de hilos
A pesar de que no llegué a usar un Thread heredado de QThread y sobreescribirlo el método <em>run()</em>, si que le dediqué algún tiempo a implementarlo, por por algunos fallos que no entendí, decidí no implementarlo y avanzar en la práctica.

Para mí el más fácil de implementar ha sido el Thread usando los distintos connect, debido a que emites señales, y al emitir esas señales simplemente llamas a la función de la clase que quieres, además para escribir estas líneas de código, me resultaron bastantes intuitivas.

Por otro lado, el QThreadPool, es el que usaría siempre, ya que no tienes que estar pendiente a crear nuevos recursos para los nuevos hilos, y si el sistemas es capaz de soportarlo.

##Comentarios
A pesar de haber tenido bastante tiempo para hacer esta práctica al comenzar a intentar hacerla en el SO de Windows, y tener que parar debido a que no conseguía avanzar, ha echo que más bien se quedara en la última semana.</br>

Una vez que he comenzado a hacerla en Ubuntu, la mayor parte del tiempo que he gastado ha sido en la forma de usar las distintas herramientas de Qt (QTableWidget y QTreeWidget) para poder sacar la información con un mínimo de formateo.	
