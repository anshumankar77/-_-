<?php
if($_SERVER["REQUEST_METHOD"] == "POST") {
    // Connect to the database
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "project";
    $conn = mysqli_connect($servername, $username, $password, $dbname);
    if (!$conn) {
        die("Connection failed: " . mysqli_connect_error());
    }
    
    // Get the form data
    $username = $_POST['username'];
    $email = $_POST['email'];
    $mobile = $_POST['mobile'];
    $create_password = $_POST['create_password'];
    $confirm_password= $_POST['confirm_password'];

    // Store the data in the database
    $sql = "INSERT INTO registration (username, email, mobile, create_password, confirm_password) VALUES ('$username', '$email', '$mobile', '$create_password','$confirm_password')";
    if (mysqli_query($conn, $sql)) {
        echo "New record created successfully";
        header("location:login.html");
    } else {
        echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    }
    
    // Close the database connection
    mysqli_close($conn);
}
?>