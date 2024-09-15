<?php
// Replace these values with your own database credentials
$host = "localhost";
$username = "root";
$password = "";
$database = "project";

// Connect to the database
$conn = mysqli_connect($host, $username, $password, $database);

// Check if the connection was successful
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

// Retrieve the user input from the form
$email = $_POST["email"];
$password = $_POST["password"];

// Prepare the SQL query to check if the user exists in the database
$sql = "SELECT * FROM registration WHERE email='$email' AND create_password='$password'";

// Execute the query
$result = mysqli_query($conn, $sql);

// Check if the query was successful
if ($result && mysqli_num_rows($result) > 0) {
    // User exists in the database
    //echo "Login successful!";
    header ("location:firstpageAL.html");
} else {
    // User does not exist in the database
    echo "Invalid email or password.";
}

// Close the database connection
mysqli_close($conn);
?>