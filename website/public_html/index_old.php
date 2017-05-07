<!doctype html>
<html>
  <head>
    <title>Temperature Guardian</title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
	<script src="../justgage-1.2.2/raphael-2.1.4.min.js"></script>
    <script src="../justgage-1.2.2/justgage.js"></script>
	
	<!--Import des XML-Files mit den Temperatur-Values-->
	<?php
		include 'example.php';

		$report = new SimpleXMLElement($xmlstr);
	?>
	
    <style>
      body {
        text-align: center;
      }

      #s1, #s2, #s3, #s4, #s5, #s6, #s7, #s8{
        width:100px; height:80px;
        display: inline-block;
        margin: 1em;
      }

      #t1, #t2, #t3, #t4, #t5, #t6, #t7, #t8{
          width:100px; height:20px;
          display: inline-block;
      }
      
      p {
        display: block;
        width: 450px;
        margin: 2em auto;
        text-align: left;
      }
	  
    </style>

	</head>
  <body>
    <div id="p">Temperaturüberprüfung mittels Sensoren<br>
	<p id="demo"></p>
     
<!-- Auslesen der Werte aus dem XML-File-->
<?php
$var = array(8);
$i = 0;
foreach ($report->sensor as $sensor){	
	$var[$i] = $sensor->temperature;
	$i++;
}
?>

</div>	  	  
	  
    <div id="s1"></div>
    <div id="t1">inaktiv</div>
    <div id="s2"></div>
    <div id="t2">inaktiv</div>
    <div id="s3"></div>
    <div id="t3">inaktiv</div>
    <div id="s4"></div>
    <div id="t4">inaktiv</div>
    <div id="s5"></div>
    <div id="t5">inaktiv</div>    
    <div id="s6"></div>
    <div id="t1">inaktiv</div>
    <div id="s7"></div>
    <div id="t1">inaktiv</div>
    <div id="s8"></div>
    <div id="t1">inaktiv</div>
	
	<script>
		const valueArray = new Array(8);
		var xhttp = new XMLHttpRequest();
		xhttp.onreadystatechange = function(){
			if (this.readyState == 4 && this.status == 200) {
				readXMLNode(this);
			}		
		}
		xhttp.open("GET", "sensordata.xml", true);
		xhttp.send();
                
		
	function readXMLNode(xml){
		var xmlDoc = xml.responseXML;
                                                       
		//document.getElementById("demo").innerHTML = xmlDoc.getElementsByTagName("SensorValues")[0].getElementsByTagName("Sensor")[0].getAttribute("value");
		for (var i = 0, len = valueArray.length; i < len; i++) {
			valueArray[i] = xmlDoc.getElementsByTagName("SensorValues")[0].getElementsByTagName("Sensor")[i].getAttribute("value");
		}               		
 
	}
	
    document.addEventListener("DOMContentLoaded", function(event) {
    var s1, s2, s3, s4, s5, s6, s7, s8;
		  
      var s1 = new JustGage({
        id: "s1",
        value: 0,
        min: 0,
        max: 75,
        title: "Sensor 1",
        hideMinMax: true
      });
	  
      var s2 = new JustGage({
        id: "s2",
        value: 0,
        min: 0,
        max: 75,
        title: "Sensor 2",
        hideMinMax: true
      });

      var s3 = new JustGage({
        id: "s3",
        value: 0,
        min: 0,
        max: 75,
        title: "Sensor 3",
        hideMinMax: true
      });

      var s4 = new JustGage({
        id: "s4",
        value: 0,
        min: 0,
        max: 75,
        title: "Sensor 4",
        hideMinMax: true
      });


      var s5 = new JustGage({
        id: "s5",
        value: 0,
        min: 0,
        max: 75,
        title: "Sensor 5",
        hideMinMax: true
      });

      var s6 = new JustGage({
        id: "s6",
        value: 0,
        min: 0,
        max: 75,
        title: "Sensor 6",
        hideMinMax: true
      });
      
      var s7 = new JustGage({
        id: "s7",
        value: 0,
        min: 0,
        max: 75,
        title: "Sensor 7",
        hideMinMax: true
      });
      
      var s8 = new JustGage({
        id: "s8",
        value: 0,
        min: 0,
        max: 75,
        title: "Sensor 8",
        hideMinMax: true
      });

                document.getElementById('t1').innerHTML='aktiv';

        setInterval(function() {
            if(valueArray[0] != null){
                s1.refresh(valueArray[0]);
                document.getElementById('t1').innerHTML='aktiv';
            }
                document.getElementById('t1').innerHTML='inaktiv';
                
          s2.refresh(valueArray[1]);
          s3.refresh(valueArray[2]);		  
//          s4.refresh(1,75, {title:"new value"});	
//          s5.refresh(getRandomInt(0, 100));
//          s6.refresh(getRandomInt(0, 100));
//          s7.refresh(getRandomInt(0, 100));
//          s8.refresh(getRandomInt(0, 100));
        }, 1000);

    });
    </script>
  </body>
</html>
