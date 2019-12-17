<!DOCTYPE html>
<html lang="en">
<head>
  <title>Rocket Search</title>
  <meta charset="utf-8">
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">

    <link rel="stylesheet" type="text/css" href="/jsgrid/demos/demos.css" />
    <link rel="stylesheet" type="text/css" href="/jsgrid/css/jsgrid.css" />
    <link rel="stylesheet" type="text/css" href="/jsgrid/css/theme.css" />
    <script src="/jsgrid/external/jquery/jquery-1.8.3.js"></script>
    <script src="/jsgrid/src/jsgrid.core.js"></script>
    <script src="/jsgrid/src/jsgrid.load-indicator.js"></script>
    <script src="/jsgrid/src/jsgrid.load-strategies.js"></script>
    <script src="/jsgrid/src/jsgrid.sort-strategies.js"></script>
    <script src="/jsgrid/src/jsgrid.field.js"></script>
    <script src="/jsgrid/src/fields/jsgrid.field.text.js"></script>
    <script src="/jsgrid/src/fields/jsgrid.field.number.js"></script>
    <script src="/jsgrid/src/fields/jsgrid.field.select.js"></script>
    <script src="/jsgrid/src/fields/jsgrid.field.checkbox.js"></script>

	<!-- Textbox Style-->
	<link href="css-input.css" rel="stylesheet" type="text/css" media="all">
	
	<!-- Button Style-->
	<link href="button.css" rel="stylesheet" type="text/css" media="all">
	
	
	<style>
	body
	{
		background-color: lightblue;
	}

	h3
	{
		color: black;
		text-align: left;
		font-family: tahoma;
	}

	.jsgrid-cell 
	{ 
		word-wrap: break-word; 
	}
	</style>

  </head>
<body>
   

        
		  
<?php
ini_set('max_execution_time', 3600);
ini_set('memory_limit', '4096M');


//config.cfg einlesen#########################################################################################################################################################################################################################################################################################################################
//######################################################################################################################################################################################################################################################
//######################################################################################################################################################################################################################################################
//######################################################################################################################################################################################################################################################
//$config_inhalt = file_get_contents('config.cfg', true);
$handle = fopen("config.cfg", "r");
if ($handle)
	{
		while (($config_inhalt = fgets($handle)) !== false) {
			
		//Redis Server IP
		//echo "<br/><br/>";
		//echo "config_inhalt: ".$config_inhalt;
		//echo "<br/><br/>";
		$pos_redis_server = strpos($config_inhalt, "redis server");
		//echo "<br/><br/>";
		//echo "pos_redis_server:".$pos_redis_server;
		//echo "<br/><br/>";
		if ($pos_redis_server !== false)
		{
			//echo "<br/><br/>";
			//echo "redis server".$config_inhalt;
			//filter IP nach dem =
			$redis_ip = substr($config_inhalt, 15 );
			//echo "redis_ip:".$redis_ip;
			rtrim($redis_ip, "\r\n");
			$redis_ip = trim($redis_ip);
			//echo "<br/><br/>";
		}
		
		//Redis Server Port
		$pos_redis_port = strpos($config_inhalt, "redis port");
		if ($pos_redis_port !== false)
		{
			//echo "<br/><br/>";
			//echo "pos_redis_port server".$config_inhalt;
			//filter Port nach dem =
			$redis_port = substr($config_inhalt, 13 );
			//echo "redis_port:".$redis_port;
			rtrim($redis_port, "\r\n");
			$redis_port = trim($redis_port);
			//echo "<br/><br/>";
		}
		
		//web replacement für die besser Darstellung für Windows Users#####
		$web_replacement_0 = $config_inhalt;
		$pos_web_replacement = strpos($config_inhalt, "web replacement");
		if ($pos_web_replacement !== false)
		{
			//echo "<br/><br/>";
			//echo "pos_web_replacement".$config_inhalt;
			//filter alle replacements
			$pos_semicolon = strpos($config_inhalt, ";");
			//echo "pos_semicolon:".$pos_semicolon;
			//echo "<br/><br/>";
			
			//nächstes Semikolon suchen und filter
			//for ($i = 0; $i < 5; $i++)
			while ($pos_semicolon == true)
			{
				$web_replacement_1 = substr($web_replacement_0,$pos_semicolon + 1);
				//echo "web_replacement_1#".$web_replacement_1;
				//echo "<br/><br/>";
				
				$pos_semicolon_ende = strpos($web_replacement_1, ";");
				//echo "pos_semicolon_ende".$pos_semicolon_ende;
				//echo "<br/><br/>";
				$web_replacement_2 = substr($web_replacement_1,0, $pos_semicolon_ende);
				//echo "web_replacement_2#".$web_replacement_2;
				//echo "<br/><br/>";
				//$web_replacement_2 in Arry speicher für späteres jsgrid herausfiltern ????
				$web_replacement_array[] = $web_replacement_2;
				//echo sizeof($web_replacement_array);
				//echo "<br/><br/>";
				
				//Pfad und Replacement separieren##########################################################
				/*
				$pos_pfeil =  strpos($web_replacement_2, "=>");
				//echo "pos_pfeil#".$pos_pfeil;
				//echo "<br/><br/>";
				$org_pfad = substr($web_replacement_2,0 ,$pos_pfeil);
				//echo "org_pfad#".$org_pfad;
				//echo "<br/><br/>";
				$replacemend_pfad = substr($web_replacement_2,$pos_pfeil + 3);
				//echo "replacemend_pfad#".$replacemend_pfad;
				//echo "<br/><br/>";
				//Pfade in Array schreiben
				*/
				//#####################################################################################
				
				
				$web_replacement_0_len = strlen($web_replacement_0);
				//echo "web_replacement_0_len#".$web_replacement_0_len;
				//echo "<br/><br/>";
				$web_replacement_0 = substr($web_replacement_1,$pos_semicolon_ende -1 )	;
				//echo "web_replacement_0#".$web_replacement_0;
				//echo "<br/><br/>";
				
				$pos_semicolon = strpos($web_replacement_0, ";");
				//echo "pos_semicolon#".$pos_semicolon;
				//echo "<br/><br/>";
				//if ($pos_semicolon == false)
				//{
				//	echo "ENDE";
				//	echo "<br/><br/>";
				//}
				//echo "pos_semicolon#".$pos_semicolon;
				//echo "<br/><br/>";
				//echo "LOOP";
				//echo "<br/><br/>";
				//$pos_web_replacement_2 =  strpos($web_replacement_1, ";");
				//echo "pos_web_replacement_2#".$pos_web_replacement_2;
				//echo "<br/><br/>";
				
				//$web_replacement_array[] = $inhalt;
				//echo "SEMIKOLON";
			}
			
			//echo "redis_port:".$redis_port;
			//rtrim($redis_port, "\r\n");
			//$redis_port = trim($redis_port);
			//echo "<br/><br/>";
		}
		//#####
		
		//Anzahl Rückgabewerte für jsgrid
		$pos_anzahl_rueckgabewerte = strpos($config_inhalt, "anzahl rueckgabewerte fuer grid");
		if ($pos_anzahl_rueckgabewerte !== false)
		{
			//echo "<br/><br/>";
			//echo "pos_redis_port server".$config_inhalt;
			//filter Port nach dem =
			$anzahl_rueckgabewerte_jsgrid = substr($config_inhalt, 33 );
			rtrim($anzahl_rueckgabewerte_jsgrid, "\r\n");
			$anzahl_rueckgabewerte_jsgrid = trim($anzahl_rueckgabewerte_jsgrid);
			//echo "anzahl_rueckgabewerte_jsgrid:".$anzahl_rueckgabewerte_jsgrid;
			//echo "<br/><br/>";
		}
		
		//else
		//{
		//	echo "<br/><br/>";
		//	echo "NIX";
		//	echo "<br/><br/>";
		//}
    }
		fclose($handle);	
	}
 else 
	{
    	echo "<br/><br/>";
		echo "TUT NET";
		echo "<br/><br/>";
	} 
//######################################################################################################################################################################################################################################################
//######################################################################################################################################################################################################################################################
//######################################################################################################################################################################################################################################################

echo '<form action="'.$_SERVER["PHP_SELF"].'" method="post">';
//echo '<textarea name="TA" cols="50" rows="1" style="resize:none" maxlength="100" onkeypress="return submitViaEnter(event)">';
echo '<div align="center">';
//echo '<input name="TA" type="text"  maxlength="100" cols="50" style="text-align:left;"/>';
echo '<input name="TA" type="text" size="100" maxlength="100" cols="50" style="text-align:left;" class="css-input"  href="css-input.css" />';
/*
if (isset($_REQUEST["TA"])) 
{
    echo $_REQUEST["TA"];
}
*/
//echo '</textarea>'."<br />\n"."<br />\n";
echo '</input>';
echo "<br/><br/>";
echo '<input type="submit" value="suchen" class="button" id="cssDisplay" href="button.css" >';
echo '</div>';
echo '</form>';
	
setlocale (LC_TIME, 'de_DE');
//$start_zeit_normal = time();
//$start_zeit_micro = microtime();

//echo "start_zeit_micro: ".$start_zeit_micro;
//echo "<br/>\n";
//echo "start_zeit_normal: ".$start_zeit_normal;
//echo "<br/>\n";

//$pfad_array[] = '';
$pfad_array =  array();
$pfad_array_groesse = sizeof($pfad_array);
$pfad_array_groesse = 0;
//echo "pfad_array_groesse: ".$pfad_array_groesse;
//echo "<br/>";

$inhalt_array =  array();
//$inhalt_array_groesse = sizeof($inhalt_array);
$inhalt_array_groesse = -1;
$pos_ok = -1;

$raw_inhalt_array =  array();
$raw_inhalt_array_groesse = sizeof($raw_inhalt_array);
$raw_inhalt_array_groesse = 0;

$start_zeit_micro = 0;
//#####################################################################
//ASCII Art Rackete einblenden
echo "
<style>

	#toplink2
	{ 
    position: fixed;
	//position: flexible;
    top: 0px !important;
    //right: 0px !important;
	left: 0px !important;
    width: 100px;
    height: 200px;
	color: black;
	text-decoration: none;
	//font-weight: bold;
	text-align: center;
	font-family: \"Tahoma\";
	font-size: 10px;
	//margin-left: 0px;
	}
	</style>

<p id=\"toplink2\">
<br/>
ROCKET SEARCH <br/>
 <br/>
   /   \ <br/>
|  | <br/>
|  | <br/>
|  | <br/>
 /____\ <br/>
 ### <br/>
 # <br/>
 </p>
 ";
//#####################################################################
//Anzahl Datensätze ausgeben
//$fp2 = fsockopen("172.17.190.78", 6379, $errno, $errstr, 300);
$fp2 = fsockopen($redis_ip, $redis_port, $errno, $errstr, 300);
	//if (!$fp2) 
	//	{
	//		echo "$errstr ($errno)<br />\n";
	//	} 
	//else 
		//{
			$out = "dbsize\r\n";
			$out .= "quit\r\n";
			
			fwrite($fp2, $out);
			
			//while (!feof($fp2)) 
			for ($i = 0; $i < 1; $i++)
			{
				$anzahl_datensaetze = fread($fp2,128);
				//echo "Datensätze: ".$anzahl_datensaetze;
				//echo "<br/>";
				//echo "<br/>";
				
				$anzahl_datensaetze = substr($anzahl_datensaetze, 0, strpos($anzahl_datensaetze, "+OK"));
				
//################################################################################
echo "
	<style>

	#toplink
	{ 
    position: fixed;
	//position: flexible;
    top: 150px !important;
	//bottom: 0px !important;
    left: 10px !important;
    width: 100px;
    height: 200px;
	color: black;
	text-decoration: none;
	//font-weight: bold;
	font-size: 10px;
	}
	</style>
	<p id=\"toplink\"> Datensätze ".$anzahl_datensaetze."</p>
	";
//################################################################################
				echo "<br/>";
				echo "<br/>";
				$i++;
				//Falls keine Datensätze in der DB hier ein "exit"
			}
		//}
fclose($fp2);
//#####################################################################

if (isset($_REQUEST["TA"])) 
	{

		$start_zeit_micro = microtime(true);	
	
		$lines = $_REQUEST["TA"];
		
		//######################################
		//Eingabe prüfen und suche verhindern
		//echo "lines: ".$lines;
		//echo "<br/>";
		$leer ="";
		$return_leer = strcasecmp($lines, $leer);
		//echo "return_leer#".$return_leer;
		//echo "<br/>";
		if ($return_leer == 0)
		{
			//echo "keine suchkriterien";
			//echo "<br/>";
			exit;
		}
		//###
		$leer_stern ="*";
		$return_leer = strcasecmp($lines, $leer_stern);
		//echo "return_leer#".$return_leer;
		//echo "<br/>";
		if ($return_leer == 0)
		{
			//echo "sternchen";
			//echo "<br/>";
			exit;
		}
		//###
		//Alle Sternchen bwz. zwei sternchen ** umwandel , für alles anzeigen, da sonst dieverese subfunktionen abtürzen
		//###
		//Wenn kein Pfad bei ##PFAD## dann die Eingabe anpassen.
		//#######################################
		

		//Suche Formatieren bzw Eingabe in der Suchmaske##############################################################
		//zeilenumbrüche entfernen
		$lines = str_replace (array("\r\n", " ", " "), ' ', $lines);
		//echo "Suchstring: ".$lines;
		$lines = "\"*".$lines."*\"";
		$suchstring_ausgabe_angepasst = $lines;
		//$suchstring_ausgabe_angepasst = str_replace (array("*", " ", " "), '', $suchstring_ausgabe_angepasst);
		$suchstring_ausgabe_angepasst = str_replace (array("*"), '', $suchstring_ausgabe_angepasst);
		echo "<br/><br/>";
		echo "<br/><br/>";
		echo "<br/><br/>";
		echo "<h3>Suchstring: ".$suchstring_ausgabe_angepasst."</h3>";
		//#Sonderzeichen durch sternchen ersteznen#######
		$lines = str_replace("[", '*', $lines);
		$lines = str_replace("]", '*', $lines);
		//echo "lines:".$lines;
		//echo "<br/><br/>";
		//**********************************************
		//Sucheingabe klien machen da redis case sensitive ist.
		$lines = strtolower($lines);
		//echo "<h3>lines: ".$lines."</h3>";
		//###########
		
		//$fp = fsockopen("172.17.190.78", 6379, $errno, $errstr, 300);
		$fp = fsockopen($redis_ip, $redis_port, $errno, $errstr, 300);

		if (!$fp) 
		{
			echo "$errstr ($errno)<br />\n";
		} 
		else 
		{
			$out = "dbsize\r\n";
			//echo $out;
			$out = "KEYS ".$lines."\r\n";
			//echo $out;
			$out .= "quit\r\n";
			//echo $out;
			fwrite($fp, $out);

			$i = 0;

			while (!feof($fp)) 
			{
				//echo fgets($fp, 1280);
				//echo "<br/>\n";
//####################################################################
//Praxis beobachtung test was besser fgets oder fread ?????????????????
//$inhalt = fgets($fp,64);
$inhalt = fread($fp,128);
//####################################################################
				//echo "RAW: ".$inhalt;
				//echo "<br/>";
				//echo "<br/>";
				$raw_inhalt_array[] = $inhalt;
				
				//################################################################
				//Anzahl der Rückgabewerte filtern und Funkion beenden falls zu viele#######
				//echo "Anzahl Rückgabewerte: ".$raw_inhalt_array[0];
				$anzahl_gefundener_objekte = $raw_inhalt_array[0];
				$pos_erstes_dollar = strpos($anzahl_gefundener_objekte, "$");
				$anzahl_gefundener_objekte = substr($anzahl_gefundener_objekte, 1, $pos_erstes_dollar - 1);
				//echo "<h3>Anzahl Rückgabewerte RAW#".$anzahl_gefundener_objekte."</h3>";
				//echo "<br/>";
				//echo "anzahl_rueckgabewerte_jsgrid#".$anzahl_rueckgabewerte_jsgrid;
				//echo "<br/>";
				//echo "anzahl_rueckgabewerte_jsgrid#intval#".intval($anzahl_rueckgabewerte_jsgrid);
				//echo "<br/>";
				//echo "is_numeric#".is_numeric($anzahl_rueckgabewerte_jsgrid);
				//echo "<br/>";
				//echo "ctype_digit#".ctype_digit($anzahl_rueckgabewerte_jsgrid);
				//Beobachten bei sehr vielen Dateien!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!###################################################################
				//if ($anzahl_gefundener_objekte > 1000)
				if ($anzahl_gefundener_objekte > $anzahl_rueckgabewerte_jsgrid)
				{
					echo "<br/>";
					echo "<h3>Zu viele Ergebniss, bitte Suche prezisieren</h3>";
					//echo "anzahl_gefundener_objekte: ".$anzahl_gefundener_objekte;
					echo "<br/>";
					exit;
				}
				//################################################################
	
			}
			
			fclose($fp);
		}
	}
//########################################################################################################	
//fclose($fp);

//Anzahle der Gefunden Objekte in der DB
if ( !empty($raw_inhalt_array))
{
	$anzahl_gefundener_objekte = $raw_inhalt_array[0];
	$pos_erstes_dollar = strpos($anzahl_gefundener_objekte, "$");
	$anzahl_gefundener_objekte = substr($anzahl_gefundener_objekte, 1, $pos_erstes_dollar - 1);
	/*
	if ($anzahl_gefundener_objekte > 10000)
	{
		echo "Zu viele Ergebniss, bitte Suche prezisieren";
		echo "<br/>";
		exit;
	}
	*/
	
	//Wenn nichts gefiunde wird ("0 +OK ) hier abbrechen
	$nichts_gefunden = "*0 +OK ";
	$return = strcasecmp($nichts_gefunden, $anzahl_gefundener_objekte);
	//echo "retrun#".$return;
	//echo "<br/>";

	if ($return == -6)
	{
		echo "nichts gefunden";
		echo "<br/>";
		exit;
	}
	else
	{
		echo "<h3>Anzahl Rückgabewerte: ".$anzahl_gefundener_objekte."</h3>";
		echo "<br/>";
	}
}

//Raw Inhalt Array formatiert ausgeben
$raw_inhalt_array_groesse = sizeof($raw_inhalt_array);
//echo "<br/>";
//echo "raw_inhalt_array_groesse: ".$raw_inhalt_array_groesse;
//echo "<br/>";

//Alle Array Inhalte in EINEN string schreiben.
$inhalt_2 ='';
for ($i = 0; $i < $raw_inhalt_array_groesse; $i++)
{
	//echo "Inhalt RAW Array: ".$raw_inhalt_array[$i];
	//echo "<br/>";
	$inhalt = $raw_inhalt_array[$i];
	$inhalt_2 .= $inhalt;
	
}
//echo "inhalt_2#".$inhalt_2."#";
//echo "<br/>";

$nichts_gefunden = "*0 +OK ";
$return = strcasecmp($nichts_gefunden, $inhalt_2);
//echo "retrun#".$return;
//echo "<br/>";

if ($return == 19)
{
	echo "nichts gefunden";
	echo "<br/>";
	exit;
}

//RAW Array leeren
unset($raw_inhalt_array); 

//Filter jeden Datensatz auf "@@ENDE@@"
//echo "<br/>";
//echo "inhalt_2: ".$inhalt_2;
//echo "<br/>";
$pos_ende = 0;
//echo "<br/>";
//echo "pos_ende NUll: ".$pos_ende;
//echo "<br/>";
$pos_ende = strpos($inhalt_2, "@@ENDE@@");
//echo "pos_ende 1: ".$pos_ende;
//echo "<br/>";
$pos_ende = strrpos($inhalt_2, '@@ENDE@@');
//echo "pos_ende reverse: ".$pos_ende;
//echo "<br/>";
//echo "<br/>";
$datensatz = substr($inhalt_2, 0, 517);
//echo "datensatz: ".$datensatz;
//echo "<br/>";

//$control_i = 0;
//Einzelne Datensaätze filter delimeter "@@ENDE@@"

$pfad_array =  array();
$pfad_array_groesse = sizeof($pfad_array);
$pfad_array_groesse = 0;


while ($pos_ende > 0)
{
	$pos_ende = strpos($inhalt_2, '@@ENDE@@');
	//echo "<br/>";
	//echo "pos_ende 2: ".$pos_ende;
	//echo "<br/>";
	//$datensatz = substr($inhalt_2, 0, $pos_ende);
	$datensatz = substr($inhalt_2, 0, $pos_ende);

	$inhalt_2 =  substr($inhalt_2, $pos_ende + 8);
	//echo "<br/>";
	//echo "datensatz: ".$datensatz;
	//echo "<br/>";
	//echo "<br/>";
	//echo "inhalt_2: ".$inhalt_2;
	//echo "<br/>";
	//echo "control_i: ".$control_i;
	//$control_i++;
//########################################################################################################

	//PFAD
	//$pos_dateiname = strpos($inhalt_2, "#DATEINAME#");
	$pos_dateiname = strpos($datensatz, "#DATEINAME#");
	//echo "pos_dateiname :".$pos_dateiname;
	//echo "<br/>";
	if ($pos_dateiname > 0)
	{

		//echo "<br/>";
		//###############################
		//die ersten beiden "zeilen" löschen ( *1 $478)
		$pos_erster_slash = strpos($datensatz, "/");
		//echo "pos_erster_slash: ".$pos_erster_slash;
		//echo "<br/>";
		//###############################
		//echo "DATEINAME";
		$pfad = substr($datensatz, $pos_erster_slash, $pos_dateiname - $pos_erster_slash);
		$pfad = str_replace (array("#PFAD#", " ", " "), ' ', $pfad);
	
		//UNC Windows Konvertierung##################################
		//echo "VOR UNC PFAD: ".$pfad;
		//echo "<br/>";
		//echo "<br/>";
//Aus webreplacement array die entsprechnden werde lesen, filtern und setzen.###########################
//$pfad = str_replace (array("/"), '\\\\', $pfad);
//$pfad = str_replace (array("\\root\\"), "\\\\\\172.17.190.34\\", $pfad);
###
//echo sizeof($web_replacement_array);
//echo "<br/>";
for ($i = 0; $i < sizeof($web_replacement_array) - 1; $i++)
{
	//echo "web_replacement_array".$web_replacement_array[$i];
	//echo "<br/>";
	//echo "<br/>";
	//Pfad und Replacement separieren##########################################################
	$pos_pfeil =  strpos($web_replacement_array[$i], "=>");
	//echo "pos_pfeil#".$pos_pfeil;
	//echo "<br/><br/>";
	$org_pfad = substr($web_replacement_array[$i],0 ,$pos_pfeil);
	//echo "org_pfad#".$org_pfad;
	//echo "<br/><br/>";
	$replacemend_pfad = substr($web_replacement_array[$i],$pos_pfeil + 3);
	//echo "replacemend_pfad#".$replacemend_pfad;
	//echo "<br/><br/>";
	//##ersetzen
	rtrim($org_pfad, "\r\n");
	$org_pfad = trim($org_pfad);
	rtrim($replacemend_pfad, "\r\n");
	$replacemend_pfad = trim($replacemend_pfad);
	$pfad = str_replace (array($org_pfad), $replacemend_pfad, $pfad);
	//echo "pfad#".$pfad;
	//echo "<br/><br/>";
	$pfad_2 = str_replace (array("/"), '\\', $pfad);
	$pfad_3 = str_replace (array("\\"), '\\\\', $pfad_2);
	//echo "pfad_3#".$pfad_3;
	//echo "<br/><br/>";
	//#####################################################################################
}
###########################
		//$pfad = preg_replace('/[root]/', '172.17.190.12', $pfad);
		//###########################################################
		//echo "PFAD: ".$pfad;
		//echo "<br/>";
		//echo "<br/>";
		//$pfad_array[] = $pfad;
		$pfad_array[] = $pfad_3;
		//$GLOBALS[$pfad_array[] = $pfad];
		//$pfad_array_groesse = sizeof($pfad_array);
		//$pfad_array_groesse = pfad_array();
		//echo $pfad_array_groesse;
		///echo "<br/>";
	}
	
	//Dateiname filtern
	$pos_letzt_zug = strpos($datensatz, "#LETZ.ZUG#");
	//echo "<br/>";
	//echo "pos_letzt_zug:".$pos_letzt_zug;
	//echo "<br/>";
	if ($pos_letzt_zug > 0)
	{
		$dateiname = substr($datensatz,$pos_dateiname + 11, $pos_letzt_zug);
		$pos_letzt_zug_2 = strpos($dateiname, "#LETZ.ZUG#");
		$dateiname = substr($dateiname,0,  $pos_letzt_zug_2);
		//echo "Dateiname: ".$dateiname;
		//echo "<br/>";
		$dateiname_array[] = $dateiname;
	}
	
	//Letzter Zugriff filtern
	$pos_letzt_mod = strpos($datensatz, "#LETZT.MOD#");
	//echo "<br/>";
	//echo "pos_letzt_mod:".$pos_letzt_mod;
	//echo "<br/>";
	if ($pos_letzt_mod > 0)
	{
		$letzter_zugriff = substr($datensatz,$pos_letzt_zug + 10, $pos_letzt_mod);
		$letzter_zugriff_2 = strpos($letzter_zugriff, "#LETZT.MOD#");
		$letzter_zugriff = substr($letzter_zugriff,0,  $letzter_zugriff_2);
		//echo "letzter_zugriff: ".$letzter_zugriff;
		//echo "<br/>";
		$letzter_zugriff_array[] = $letzter_zugriff;
	}
	
	//Letzte Modifikation
	$pos_create_date = strpos($datensatz, "#CREATE.DATAE#");
	//echo "<br/>";
	//echo "pos_create_date:".$pos_create_date;
	//echo "<br/>";
	if ($pos_create_date > 0)
	{
		$letzt_mod = substr($datensatz,$pos_letzt_mod + 11, $pos_create_date);
		$letzt_mod_2 = strpos($letzt_mod, "#CREATE.DATAE#");
		$letzt_mod = substr($letzt_mod,0,  $letzt_mod_2);
		//echo "letzt_mod: ".$letzt_mod;
		//echo "<br/>";
		$letzt_mod_array[] = $letzt_mod;
		
	}
	
	//Erstelldatum
	$pos_erstell_datum = strpos($datensatz, "#CREATE.DATAE#");
	//echo "<br/>";
	//echo "pos_erstell_datum:".$pos_erstell_datum;
	//echo "<br/>";
	
	if ($pos_erstell_datum > 0)
	{
		$erstell_datum = substr($datensatz,$pos_erstell_datum + 14);
		$erstell_datum_2 = strpos($erstell_datum, "#SIZE#");
		$erstell_datum = substr($erstell_datum,0,  $erstell_datum_2);
		//echo "erstell_datum: ".$erstell_datum;
		//echo "<br/>";
		$erstell_datum_array[] = $erstell_datum;
	}
	
	//size
	$pos_size = strpos($datensatz, "#SIZE#");
	//echo "<br/>";
	//echo "pos_size:".$pos_size;
	//echo "<br/>";
	
	if ($pos_size > 0)
	{
		$size = substr($datensatz,$pos_size + 6);
		$size_2 = strpos($size, "#MD5#");
		$size = substr($size,0,  $size_2);
		//Size in MB und GB Umrechnen
		//bytes nach MB ((x / 1024)/1024)
		$size_2 = floatval (strval(($size/1024)/1024));
		//echo "size: ".$size;
		//echo "<br/>";
		$size_2 = number_format($size_2, 2, '.', '');
		//echo "size: ".$size_2." MB";
		//echo "<br/>";
		$size_2_datum_array[] = $size_2;
	}
	
	//MD5
	$pos_md5 = strpos($datensatz, "#MD5#");
	if ($pos_md5 > 0)
	{
		$md5 = substr($datensatz,$pos_md5 + 5);
		$md5_2 = strpos($md5, "#INHALT#");
		$md5 = substr($md5,0,  $md5_2);
		//echo "md5: ".$md5;
		//echo "<br/>";
		$md5_datum_array[] = $md5;
	}
	
	$pos_inhalt = strpos($datensatz, "#INHALT#");
	//echo "pos_inhalt: ".$pos_inhalt;
	//$inhalt_controller = false;
	//echo "<br/>";
	
	if ($pos_inhalt > 0)
	{
		//echo "datensatz: ".$datensatz;
		//echo "<br/>";
		$datei_inhalt = substr($datensatz,$pos_inhalt + 8);
		//echo "datei_inhalt VOR: ".$datei_inhalt;
		//echo "<br/>";
		$pos_ende_2 = strpos($datei_inhalt, '@@ENDE@@');
		//$inhalt_array[] = $datei_inhalt_2;
		
		//rtrim($datei_inhalt, "\r\n");
		//$datei_inhalt = trim($datei_inhalt);
		
		$inhalt_array[] = $datei_inhalt;
		
		if ($pos_ende_2 <= 0)
		{
			//echo "pos_ende_2 gleich NULL: ".$pos_ende_2;
			//echo "<br/>";
			continue;
		}
		
		$datei_inhalt_2 = substr($datei_inhalt,0, $pos_ende_2);
		//echo "pos_ende_2: ".$pos_ende_2;
		//echo "<br/>";
		//echo "pos_ende_2: ".$pos_ende_2;
		//$pos_ok = strpos($datei_inhalt, "+OK");
		//echo "<br/>";
		//echo "pos_ok: ".$pos_ok;
		//$inhalt = substr($inhalt,$pos_inhalt,$pos_ok);
		//echo "datei_inhalt_2 NACH: ".$datei_inhalt_2;
		//echo "<br/>";
		//echo "<br/>";
		//echo "<br/>";
		//$inhalt_array[] = $datei_inhalt;
		//$inhalt_controller = true;
	}
//########################################################################################################
//fclose($fp);

}


//########################################################################################################	
//Alle jetzt nutzlosen array leeren (inhalt inhalt_2 uvm) prüfen !!!!!

//RAW inhalt_2 leeren, alle Infos sollten nun in den einzelnen arrays stehen.
//echo $datensatz;
unset($inhalt_2);
//unset($datensatz);

//Zeit
$suchzeit_normal = 0;
if ($start_zeit_micro != 0)
{
	$end_zeit_normal = microtime(true);
	$suchzeit_normal = $end_zeit_normal - $start_zeit_micro;
}

//echo "pfad_array: ".$pfad_array[0];
//echo "<br/>";
//echo $pfad_array();
//$pfad_array_groesse = pfad_array();
$pfad_array_groesse = sizeof($pfad_array);
//echo "pfad_array_groesse: ".$pfad_array_groesse;
//echo "<br/>";


if ($pfad_array_groesse == 0)
{
	//echo "INITIAL nichts gesucht";
	//echo "<br/>";
	exit;
}

/*
for ($i = 0; $i < $pfad_array_groesse ; $i++)
{
	echo $pfad_array[$i];
	echo "<br/>";
}
*/
$var_client_js_script_anfang = ' var clients = [ ' ;
$var_client_js_script_werte2 = '';


for ($i = 0; $i < $pfad_array_groesse ; $i++)
{
	//Java Script dynamisch erweitern je nachdem wieviel Objkete aus der DB gefunbden wurden.
	//$var_client_js_script_werte = ' { "Pafd": "'.$pfad_array[$i].'", "Dateiname": "'.$dateiname_array[$i].'", "letzter Zugriff": "'.$letzter_zugriff_array[$i].'", "letzte Modifikation": "'.$letzt_mod_array[$i].'", "Erstell Datum": "'.$erstell_datum_array[$i].'" , "Size": "'.$size_2_datum_array[$i]." MB".'", "MD5": "'.$md5_datum_array[$i].'", "Inhalt": "'.$inhalt_array[$i].' " }, ';
	//########################################
	//Inhalt bearbeiten und diverse Zeichen ändern und abschneiden
	
	$string_inhalt = $inhalt_array[$i];
	//echo "<br/>";
	//echo "VOR   TRIM: ".$string_inhalt;
	//echo "<br/>";
	
	rtrim($string_inhalt, "\r\n");
	$string_inhalt = trim($string_inhalt);
	//$string_inhalt = preg_replace("/[\n|\r]/",'',$string_inhalt);
//$string_inhalt = preg_replace("/[\n\r|\r\n]/",'',$string_inhalt);
$string_inhalt = preg_replace("/[\n\r\r\n]/",'',$string_inhalt);
$string_inhalt = preg_replace("/[\"]/",'',$string_inhalt);
$string_inhalt = preg_replace("/[']/",'',$string_inhalt);
$string_inhalt = preg_replace("/[´]/",'',$string_inhalt);
$string_inhalt = preg_replace("/[`]/",'',$string_inhalt);
$string_inhalt = preg_replace("/[`]/",'',$string_inhalt);
$string_inhalt = str_replace("\"", '', $string_inhalt);
$string_inhalt = str_replace("\\", '#', $string_inhalt);
//$string_inhalt = preg_replace('/[\x00-\x1F\x7F-\xFF]/','',$string_inhalt);
//$string_inhalt = preg_replace("/[\xE2\x80\xA8]/",'',$string_inhalt);
//$string_inhalt = preg_replace("/[ ]/",'',$string_inhalt);
//$string_inhalt = preg_replace('/[�]/','',$string_inhalt);
//$string_inhalt = preg_replace('�','#',$string_inhalt);
//$string_inhalt = preg_replace("\\",'',$string_inhalt);
	//$string_inhalt = str_replace(array("\r\n", "", " "), '', $string_inhalt);
	//$string_inhalt = str_replace(array("\r\n\r\n", "", ""), '', $string_inhalt);
	//$string_inhalt = str_replace(array("\n\r", "", ""), '', $string_inhalt);
	//$string_inhalt = str_replace(array("\n\r\n\r", "", ""), '', $string_inhalt);
	
	//echo "<br/>";
	//echo "NACH TRIM: ".$string_inhalt;
	//echo "<br/>";
	
	//########################################

    //$string_inhalt = iconv('utf-16', 'us-ascii//TRANSLIT', $string_inhalt);
	//$string_inhalt = iconv('utf-8', 'us-ascii//IGNORE', $string_inhalt);
	//$string_inhalt = iconv('UTF-8', 'utf-8//TRANSLIT', $string_inhalt);
	//$string_inhalt = iconv("cp1252", "utf-16//IGNORE", $string_inhalt);
	//$string_inhalt = @iconv('UTF-16', 'utf-16//TRANSLIT', $string_inhalt);
	//$string_inhalt = @iconv('us-ascii', 'utf-16//IGNORE', $string_inhalt);
//Beobachten ob nötig, da alle Datensätze im UTF-8 format durch den "read_file_infos" in die Datenbank kommen
//$string_inhalt = iconv('us-ascii', 'utf-8//TRANSLIT', $string_inhalt);
//$string_inhalt = iconv('ISO-8859-1//TRANSLIT', $string_inhalt);
	//$string_inhalt = @iconv('cp1252', 'utf-16//IGNORE', $string_inhalt);
	/*
	if ($string_inhalt ="");
	{
		$string_inhalt= "NIX";
	}
	*/
	//echo $php_errormsg;
	//$e = error_get_last();
	//echo "e: ".$e[1];
	//$e['message'] = array_search($e['message'], get_defined_constants());
	//echo($e['message']);
	//echo "<br/>";
	//string iconv ( string $in_charset , string $out_charset , string $str )
	
	//########################################
	//echo "string_inhalt NACH TRIM: ".$string_inhalt;
	//echo "<br/>";
	//ORG ZEICHENKETTE//#EXTINF:341,Claude debussy - Clair de lune01 - Claude debussy - Clair de lune - By xEnX=PiLleR@.mp3#EXTINF:300,Wolfgang A.Mozart - Concerto for clarinet (k.581)02 - Wolfgang A.Mozart - Concerto for clarinet (k.581) - By xEnX=PiLleR@.mp3⍅塔䥎䘺㈷㔬䥳慡挠慬择湩稠�䏡摩稍o爠捬慲楮� 欮㔸ㄩ‭⁂礠硅湘㵐楌汥剀⹭瀳��03 - Isaac albéniz - Cádiz - By xEnX=PiLleR@.mp3
	//$var_client_js_script_werte = ' { "Pafd": "PFAD", "Dateiname": "DATEINAME", "letzter Zugriff": "'.$letzter_zugriff_array[$i].'", "letzte Modifikation": "'.$letzt_mod_array[$i].'", "Erstell Datum": "'.$erstell_datum_array[$i].'" , "Size": "'.$size_2_datum_array[$i]." MB".'", "MD5": "'.$md5_datum_array[$i].'", "Inhalt": "#EXTINF:341,Claude debussy - Clair de lune01 - Claude debussy - Clair de lune - By xEnX=PiLleR@.mp3#EXTINF:300,Wolfgang A.Mozart - Concerto for clarinet (k.581)02 - Wolfgang A.Mozart - Concerto for clarinet (k.581) - By xEnX=PiLleR@.mp3⍅塔䥎䘺㈷㔬䥳慡挠慬择湩稠�####� #####03 - Isaac albéniz - Cádiz - By xEnX=PiLleR@.mp3 " }, ';

//############################################################################################################################################
//####Suche "Suchstring" und markiere es in HTML rot im jsgrid
//####<font color="red">This is some text!</font>
//echo "Suchstring: ".$suchstring_ausgabe_angepasst;
//echo "<br/>";
$suchstring_html_red = $suchstring_ausgabe_angepasst;
$suchstring_html_red = strtolower($suchstring_html_red);
$suchstring_html_red = str_replace("\"", '', $suchstring_html_red);
$suchstring_html_red = str_replace("/", '\\\\', $suchstring_html_red);
//echo "suchstring_html_red:".$suchstring_html_red;
//echo "<br/>";
//echo "pfad_array[\$i]".$pfad_array[$i];
//echo "<br/>";
//$wo_ist_suchstring = strpos($pfad_array[$i], $suchstring_html_red);
//echo "pfad_array".$pfad_array[$i];
//echo "<br/>";
//echo "wo_ist_suchstring:".$wo_ist_suchstring;
//echo "<br/>";

//#PFAD###
$wo_ist_suchstring = strpos($pfad_array[$i], $suchstring_html_red);
//echo "wo_ist_suchstring:".$wo_ist_suchstring;
//echo "<br/>";
if ($wo_ist_suchstring > 0)
{
	$pfad_array_html_red = substr_replace($pfad_array[$i], '<font color=\"red\">'.$suchstring_html_red.'</font>', $wo_ist_suchstring, strlen($suchstring_html_red));
}
else
{
	$pfad_array_html_red = $pfad_array[$i];
}
//echo "pfad_array_html_red:".$pfad_array_html_red;
//echo "<br/>";
//echo "pfad_array".$pfad_array[$i];
//echo "<br/>";
//##############


//#Dateiname###
//echo"dateiname_array[i]:".$dateiname_array[$i];
//echo "<br/>";
$dateiname_offset_fuer_strpos = $dateiname_array[$i];
$dateiname_offset_fuer_strpos = " ".$dateiname_offset_fuer_strpos ;
//echo "dateiname_offset_fuer_strpos:".$dateiname_offset_fuer_strpos;
//echo "<br/>";
$wo_ist_suchstring = strpos($dateiname_offset_fuer_strpos, $suchstring_html_red);
//echo "wo_ist_suchstring:".$wo_ist_suchstring;
//echo "<br/>";
if ($wo_ist_suchstring > 0)
{
	$dateiname_array_array_html_red = substr_replace($dateiname_array[$i], '<font color=\"red\">'.$suchstring_html_red.'</font>', $wo_ist_suchstring - 1, strlen($suchstring_html_red));
}
else
{
	$dateiname_array_array_html_red = $dateiname_array[$i];
}
//##############

//#Letzter Zugriff###
//echo"letzter_zugriff_array[i]:".$letzter_zugriff_array[$i];
//echo "<br/>";
$letzter_zugriff_offset_fuer_strpos = $letzter_zugriff_array[$i];
$letzter_zugriff_offset_fuer_strpos = " ".$letzter_zugriff_offset_fuer_strpos ;
//echo "letzter_zugriff_offset_fuer_strpos:".$letzter_zugriff_offset_fuer_strpos;
//echo "<br/>";
$wo_ist_suchstring = strpos($letzter_zugriff_offset_fuer_strpos, $suchstring_html_red);
//echo "wo_ist_suchstring:".$wo_ist_suchstring;
//echo "<br/>";
if ($wo_ist_suchstring > 0)
{	
	$letzter_zugriff_array_array_html_red = substr_replace($letzter_zugriff_array[$i], '<font color=\"red\">'.$suchstring_html_red.'</font>', $wo_ist_suchstring - strlen($suchstring_html_red) -1	, strlen($suchstring_html_red));
	//echo "letzter_zugriff_array_array_html_red:".$letzter_zugriff_array_array_html_red;
	//echo "<br/>";
}
else
{
	$letzter_zugriff_array_array_html_red = $letzter_zugriff_array[$i];
}
//##############

//#Letzte Modifikation###
//echo"letzt_mod_array[i]:".$letzt_mod_array[$i];
//echo "<br/>";
$letzt_modi_offset_fuer_strpos = $letzt_mod_array[$i];
$letzt_modi_offset_fuer_strpos = " ".$letzt_modi_offset_fuer_strpos ;
//echo "letzt_modi_offset_fuer_strpos:".$letzt_modi_offset_fuer_strpos;
//echo "<br/>";
$wo_ist_suchstring = strpos($letzt_modi_offset_fuer_strpos, $suchstring_html_red);
//echo "wo_ist_suchstring:".$wo_ist_suchstring;
//echo "<br/>";
if ($wo_ist_suchstring > 0)
{	
	$letzt_mod_array_array_html_red = substr_replace($letzt_mod_array[$i], '<font color=\"red\">'.$suchstring_html_red.'</font>', $wo_ist_suchstring - strlen($suchstring_html_red) -1	, strlen($suchstring_html_red));
	//echo "letzt_mod_array_array_html_red:".$letzt_mod_array_array_html_red;
	//echo "<br/>";
}
else
{
	$letzt_mod_array_array_html_red = $letzt_mod_array[$i];
}
//##############

//MD5 SUM###
//echo"md5_datum_array[i]:".$md5_datum_array[$i];
//echo "<br/>";
$md5_hash_offset_fuer_strpos = $md5_datum_array[$i];
$md5_hash_offset_fuer_strpos = " ".$md5_hash_offset_fuer_strpos ;
//echo "md5_hash_offset_fuer_strpos:".$md5_hash_offset_fuer_strpos;
//echo "<br/>";
$wo_ist_suchstring = strpos($md5_hash_offset_fuer_strpos, $suchstring_html_red);
//echo "wo_ist_suchstring:".$wo_ist_suchstring;
//echo "<br/>";
if ($wo_ist_suchstring > 0)
{	
	$md5_hash_array_array_html_red = substr_replace($md5_datum_array[$i], '<font color=\"red\">'.$suchstring_html_red.'</font>', $wo_ist_suchstring - strlen($suchstring_html_red) -1	, strlen($suchstring_html_red));
	//echo "letzt_mod_array_array_html_red:".$md5_hash_array_array_html_red;
	//echo "<br/>";
}
else
{
	$md5_hash_array_array_html_red = $md5_datum_array[$i];
}
//##############

//Inhalt###
//echo"string_inhalt:".$string_inhalt;
//echo "<br/>";
$string_inhalt_offset_fuer_strpos = $string_inhalt;
$string_inhalt_offset_fuer_strpos = " ".$string_inhalt_offset_fuer_strpos ;
//echo "string_inhalt_offset_fuer_strpos:".$string_inhalt_offset_fuer_strpos;
//echo "<br/>";
$wo_ist_suchstring = strpos($string_inhalt_offset_fuer_strpos, $suchstring_html_red);
//echo "wo_ist_suchstring:".$wo_ist_suchstring;
//echo "<br/>";
if ($wo_ist_suchstring > 0)
{	
	$inhalt_html_red = substr_replace($string_inhalt, '<font color=\"red\">'.$suchstring_html_red.'</font>', $wo_ist_suchstring - strlen($suchstring_html_red) -1	, strlen($suchstring_html_red));
	//echo "letzt_mod_array_array_html_red:".$inhalt_html_red;
	//echo "<br/>";
}
else
{
	$inhalt_html_red = $string_inhalt;
}
//##############
//############################################################################################################################################

//$var_client_js_script_werte = ' { "Pafd": "<a href=TEST>test</a>", "Dateiname": "DATEINAME", "letzter Zugriff": "'.$letzter_zugriff_array[$i].'", "letzte Modifikation": "'.$letzt_mod_array[$i].'", "Erstell Datum": "'.$erstell_datum_array[$i].'" , "Size": "'.$size_2_datum_array[$i]." MB".'", "MD5": "'.$md5_datum_array[$i].'", "Inhalt": "INHALT " }, ';
//Normal ohne Links
//$var_client_js_script_werte = ' { "Pafd": "'.$pfad_array[$i].'", "Dateiname": "'.$dateiname_array[$i].'", "letzter Zugriff": "'.$letzter_zugriff_array[$i].'", "letzte Modifikation": "'.$letzt_mod_array[$i].'", "Erstell Datum": "'.$erstell_datum_array[$i].'" , "Size": "'.$size_2_datum_array[$i]." MB".'", "MD5": "'.$md5_datum_array[$i].'", "Inhalt": "'.$string_inhalt.' " }, ';

//UNC Konform########################################################
//UNC Pfad sind als href HTML tags meist geblock. Daher UNC copy to clipboard .http://kb.mozillazine.org/Links_to_local_pages_do_not_work
//$pfad_unc_link = $pfad_array[$i];
	//$pfad_unc_link = "\\\\\\172.17.190.34\\";
//$pfad_unc_link = "\\".$pfad_unc_link;
#$pfad_unc_link = str_replace("\\\\", '\\', $pfad_unc_link);
//$pfad_unc_link = str_replace("\\", '\\', $pfad_unc_link);
//$pfad_unc_link = str_replace(" ", '%20', $pfad_unc_link);
#$pfad_unc_link = 'file:'.$pfad_unc_link;
//$pfad_unc_link = substr($pfad_unc_link, 2, 999);
//echo "pfad_unc_link: ".$pfad_unc_link;
//echo "<br/>";
//echo "pfad: ".$pfad_array[$i];
//echo "<br/>";
//$var_client_js_script_werte = ' { "Pafd": "'.$pfad_array[$i].'", "Dateiname": "'.$dateiname_array[$i].'", "letzter Zugriff": "'.$letzter_zugriff_array[$i].'", "letzte Modifikation": "'.$letzt_mod_array[$i].'", "Erstell Datum": "'.$erstell_datum_array[$i].'" , "Size": "'.$size_2_datum_array[$i]." MB".'", "MD5": "'.$md5_datum_array[$i].'", "Inhalt": "'.$string_inhalt.' " }, ';
//$var_client_js_script_werte = ' { "Pafd": "<a href='.$pfad_unc_link.'>'.$pfad_array[$i].'</a>", "Dateiname": "'.$dateiname_array[$i].'", "letzter Zugriff": "'.$letzter_zugriff_array[$i].'", "letzte Modifikation": "'.$letzt_mod_array[$i].'", "Erstell Datum": "'.$erstell_datum_array[$i].'" , "Size": "'.$size_2_datum_array[$i]." MB".'", "MD5": "'.$md5_datum_array[$i].'", "Inhalt": "'.$string_inhalt.' " }, ';
//$var_client_js_script_werte = ' { "Pafd": "'.$pfad_array[$i].'", "Dateiname": "'.$dateiname_array[$i].'", "letzter Zugriff": "'.$letzter_zugriff_array[$i].'", "letzte Modifikation": "'.$letzt_mod_array[$i].'", "Erstell Datum": "'.$erstell_datum_array[$i].'" , "Size": "'.$size_2_datum_array[$i]." MB".'", "MD5": "'.$md5_datum_array[$i].'", "Inhalt": "'.$string_inhalt.' " }, ';

//HTML RED#############################################
$var_client_js_script_werte = ' { "Pafd": "'.$pfad_array_html_red.'", "Dateiname": "'.$dateiname_array_array_html_red.'", "letzter Zugriff": "'.$letzter_zugriff_array_array_html_red.'", "letzte Modifikation": "'.$letzt_mod_array_array_html_red.'", "Erstell Datum": "'.$erstell_datum_array[$i].'" , "Size": "'.$size_2_datum_array[$i]." MB".'", "MD5": "'.$md5_hash_array_array_html_red.'", "Inhalt": "'.$inhalt_html_red.' " }, ';

//###########################################
$var_client_js_script_werte2 .= $var_client_js_script_werte;
	
}
$var_client_js_script_ende = '];';
$var_client_js_script = $var_client_js_script_anfang.$var_client_js_script_werte2.$var_client_js_script_ende ;
//echo "<br/>";
//echo "var_client_js_script: ".$var_client_js_script;
//echo "<br/>";


echo '
<div id="jsGrid"></div>
	<script>
		'.$var_client_js_script.'

		$("#jsGrid").jsGrid({
		width: "100%",
		height: "400px",

		inserting: false,
		editing: false,
		sorting: true,
		autoencode: true,
		paging: true,
		data: clients,
		
		fields: [
		{ name: "Pafd", type: "text", width: 250 },
		{ name: "Dateiname", type: "text", width: 250 },
		{ name: "letzter Zugriff", type: "text", width: 200 },
		{ name: "letzte Modifikation", type: "text", width: 200 },
		/* { name: "Erstell Datum", type: "text",  width: 200  }, */
		{ name: "Size", type: "text",  width: 150  },
		{ name: "MD5", type: "text",  width: 270  },
		{ name: "Inhalt", type: "text",  width: 200 , encoded: false }
		]
		});
	</script>

';


//########################################################################################################	
echo "<br/>";
//echo "Ende";
echo "<br/>";
echo "<h3> Suchzeit: ".$suchzeit_normal." Sekunden</h3>";
?>

</body>
</html>
