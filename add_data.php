<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "iotdb";

#Create connection
$conn = new mysqli($servername, $username,$password, $dbname);

#Check connection
if ($conn->connect_error) 
{
    die("Connection failed: " . $conn->connect_error);
} 

#Get Values of LDR & IR sensor into variables
$val = $_GET['ldr'];
$val1 = $_GET['ir'];

#Generate SQL query
$sql = "INSERT INTO iot ( ldr, ir ) VALUES ( '$val', '$val1' )";

if ($conn->query($sql) === TRUE) {
    echo "LDR and IR data Saved Successfully!";
} 
else 
{
    echo "Error:" . $sql . "<br>" . $conn->error;
}

$conn->close();
?>