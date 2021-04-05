<!DOCTYPE html>
<html>
<head>
<title></title>
<link rel="stylesheet" href="bootstrap/css/bootstrap.min.css">
</head>

<body style="background-color:rgb(211,211,211);">
<div class="col-lg-8">
<h1>Internet Of Things</h1>
</div>
<br>
<div class="col-lg-2">
 <h3>TEAM EHC</h3>
</div>
<div class="row">
<div class="col-lg-6">
<table align="center" class="table table-striped table-dark" bgcolor="black">
    <tr></tr>
    <tr>
        <td>LDR DATA</td>
		<td>IR DATA</td>
        <td>DATE AND TIME</td>
    </tr>
	
    <?php
    $servername = "localhost";
	$username = "root";
	$password = "";
	$dbname = "iotdb";

	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	} 
    $sql="SELECT ldr,ir,day FROM iot ORDER by day DESC LIMIT 10";
    $res=$conn->query($sql);
	if($res->num_rows > 0)
	{
		while($row=$res->fetch_assoc())
		{
			echo "<tr>";
			echo "<td>".$row['ldr']."</td>";
			echo "<td>".$row['ir']."</td>";
			echo "<td>".$row['day']."</td>";
			echo "</tr>";
		}
	}
	else 
	{
		echo "0 results";
	}
	$conn->close();
    ?>
</table>
</div>
</div>
</body>
</html>