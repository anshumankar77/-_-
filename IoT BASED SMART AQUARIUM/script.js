// Your web app's Firebase configuration
var firebaseConfig = {
    apiKey: "AIzaSyCUEOtxKcTP2p1SQUs4df1UUeqj0BoJXBc",
    authDomain: "led-web.firebaseapp.com",
    databaseURL: "https://led-web.firebaseio.com",
    projectId: "led-web",
    storageBucket: "led-web.appspot.com",
    messagingSenderId: "175865998491",
    appId: "1:175865998491:web:490890ea08beff7e0f2a3e",
  };
  // Initialize Firebase
  firebase.initializeApp(firebaseConfig);

$(document).ready(function(){
	var database = firebase.database();
	var M1Status;
	var M2Status;
	// var Led3Status;
	// var Led4Status;
	database.ref().on("value", function(snap){
		M1Status = snap.val().M1Status;
		M2Status = snap.val().M2Status;
		// Led3Status = snap.val().Led3Status;
		// Led4Status = snap.val().Led4Status;
		if(M1Status == "1"){
			document.getElementById("unact").style.display = "none";
			document.getElementById("act").style.display = "block";
		} else {
			document.getElementById("unact").style.display = "block";
			document.getElementById("act").style.display = "none";
		}
		if(M2Status == "1"){
			document.getElementById("unact1").style.display = "none";
			document.getElementById("act1").style.display = "block";
		} else {
			document.getElementById("unact1").style.display = "block";
			document.getElementById("act1").style.display = "none";
		}
		// if(Led3Status == "1"){
		// 	document.getElementById("unact2").style.display = "none";
		// 	document.getElementById("act2").style.display = "block";
		// } else {
		// 	document.getElementById("unact2").style.display = "block";
		// 	document.getElementById("act2").style.display = "none";
		// }
		// if(Led4Status == "1"){
		// 	document.getElementById("unact3").style.display = "none";
		// 	document.getElementById("act3").style.display = "block";
		// } else {
		// 	document.getElementById("unact3").style.display = "block";
		// 	document.getElementById("act3").style.display = "none";
		// }
	});

	$(".toggle-btn").click(function(){
		var firebaseRef = firebase.database().ref().child("M1Status");
		if(M1Status == "1"){
			firebaseRef.set("0");
			M1Status = "0";
		} else {
			firebaseRef.set("1");
			M1Status = "1";
		}
	})
	$(".toggle-btn1").click(function(){
		var firebaseRef = firebase.database().ref().child("M2Status");
		if(M2Status == "1"){
			firebaseRef.set("0");
			M2Status = "0";
		} else {
			firebaseRef.set("1");
			M2Status = "1";
		}
	})
	// $(".toggle-btn2").click(function(){
	// 	var firebaseRef = firebase.database().ref().child("Led3Status");
	// 	if(Led3Status == "1"){
	// 		firebaseRef.set("0");
	// 		Led3Status = "0";
	// 	} else {
	// 		firebaseRef.set("1");
	// 		Led3Status = "1";
	// 	}
	// })
	// $(".toggle-btn3").click(function(){
	// 	var firebaseRef = firebase.database().ref().child("Led4Status");
	// 	if(Led4Status == "1"){
	// 		firebaseRef.set("0");
	// 		Led4Status = "0";
	// 	} else {
	// 		firebaseRef.set("1");
	// 		Led4Status = "1";
	// 	}
	// })
});