const form = document.querySelector('form');
		const errorMessage = document.querySelector('#error-message');
		
		form.addEventListener('submit', function(event) {
			event.preventDefault();
			const username = document.querySelector('#username').value;
			const password = document.querySelector('#password').value;
			
			if (username === '' || password === '') {
                alert('Please enter both username and password.');
				return;
			}
			
			alert(`Username: ${username}\nPassword: ${password}`);
		});