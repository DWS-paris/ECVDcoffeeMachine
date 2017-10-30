document.addEventListener('DOMContentLoaded', function(event) {

    /*
    Introduction
    */
        window.setTimeout(function(){
            document.querySelector('body').classList.add('open');
        }, 300);
    // 

    /*
    Variables globales
    */
        var coffeeBtns = document.querySelectorAll('.coffeeType');
        var userSelection = null;
        var myH2title = document.getElementById('myH2title');
        var randomQuestion = document.getElementById('randomQuestion');
        var formStepOne = document.getElementById('formStepOne');
        var waiter = document.getElementById('waiter');
        var restartBtn = document.getElementById('restartBtn');
        var newOrderBtn = document.getElementById('newOrderBtn');
        var blackCoffee = document.getElementById('blackCoffee');
        var sweetCoffee = document.getElementById('sweetCoffee');
        var errorMessage = document.getElementById('errorMessage');
        var randomQuestionList = document.getElementById('randomQuestionList');
        var randomQuestionTitle = document.getElementById('randomQuestionTitle');
        var questionsArray = [
            {
                id: 1,
                question: 'When did the first website appear?',
                choices: [
                    {
                        id: 1,
                        proposal: 'January 17th, 1999',
                        response: false
                    },
                    {
                        id: 2,
                        proposal: 'September 23th, 1994',
                        response: false
                    },
                    {
                        id: 3,
                        proposal: 'August 6th, 1991',
                        response: true
                    }
                ]
            },
            {
                id: 2,
                question: 'Who invented the web?',
                choices: [
                    {
                        id: 1,
                        proposal: 'Bob Kahn',
                        response: false
                    },
                    {
                        id: 2,
                        proposal: 'Timothy Berners Lee',
                        response: true
                    },
                    {
                        id: 3,
                        proposal: 'Issac Asimov',
                        response: false
                    }
                ]
            },
            {
                id: 3,
                question: 'What is the definition of http?',
                choices: [
                    {
                        id: 1,
                        proposal: 'Hypertext Transfer Protocol',
                        response: true
                    },
                    {
                        id: 2,
                        proposal: 'Hyper Text Protocol',
                        response: false
                    },
                    {
                        id: 3,
                        proposal: 'Hypertext Technology Protocol',
                        response: false
                    }
                ]
            },
            {
                id: 4,
                question: 'What statement is not accurate?',
                choices: [
                    {
                        id: 1,
                        proposal: 'A robot must obey the orders given by human beings.',
                        response: false
                    },
                    {
                        id: 2,
                        proposal: 'A robot must protect its integrity against aggression.',
                        response: true
                    },
                    {
                        id: 3,
                        proposal: 'A robot can not leave a human beings exposed to danger.',
                        response: false
                    }
                ]
            },
            {
                id: 4,
                question: 'Easy for you, what does ECV mean?',
                choices: [
                    {
                        id: 1,
                        proposal: 'École de Communication Visuelle.',
                        response: true
                    },
                    {
                        id: 2,
                        proposal: 'Envie de Croire en Vous.',
                        response: false
                    },
                    {
                        id: 3,
                        proposal: 'Etre Conscient-e de vos Valeurs.',
                        response: false
                    }
                ]
            }
        ];
        var randomQuestionNumber = Math.floor((Math.random() * 5) + 0);
        var randomChoicesArray = questionsArray[randomQuestionNumber].choices;
    //


    /*
    Configuration de la question aléatoire
    */
        randomQuestionTitle.textContent = questionsArray[randomQuestionNumber].question;

        for(var i = 0; i < randomChoicesArray.length; i++){
            var newChoiceBtn = document.createElement('button');
            newChoiceBtn.textContent = randomChoicesArray[i].proposal;
            newChoiceBtn.setAttribute('data-choice', randomChoicesArray[i].response);
            newChoiceBtn.classList.add('randomChoices');
            randomQuestionList.appendChild(newChoiceBtn);
        };

        var randomChoices = document.querySelectorAll('.randomChoices');

    //

    
    /*
    Gestion du choix du café
    */
        for(var i = 0; i < coffeeBtns.length; i++){
            coffeeBtns[i].onclick = function(){
                blackCoffee.classList.remove('active');
                sweetCoffee.classList.remove('active');

                this.classList.add('active');
                userSelection = this.getAttribute('data-coffee');
            };
        };
    //


    /*
    Gestion de la validation du choix du café
    */
        document.getElementById('goToStep2').onclick = function(){

            if(userSelection != null){
                myH2title.classList.add('hidden');
                formStepOne.classList.add('close');

                window.setTimeout(function(){
                    formStepOne.style.display = 'none';
                    myH2title.textContent = 'Select the correct response';
                    myH2title.classList.remove('hidden');                    

                    window.setTimeout(function(){
                        randomQuestion.style.display = 'block';
                        randomQuestion.classList.add('open');
    
                    }, 300);

                }, 300);

            } else{
                errorMessage.classList.add('open');
                window.setTimeout(function(){
                    errorMessage.classList.remove('open');
                }, 5000);
            };
            
        };
    //


    /*
    Gestion de la réponse à la question aléatoire
    */
        for(var i = 0; i < randomChoices.length; i++){

            randomChoices[i].onclick = function(){
                myH2title.classList.add('hidden');
                
                randomQuestion.classList.remove('open');
                window.setTimeout(function(){
                    randomQuestion.style.display = 'none';
                }, 300);

                if(this.getAttribute('data-choice') == 'true'){

                    window.setTimeout(function(){
                        myH2title.textContent = 'Your order is complete';
                        myH2title.classList.remove('hidden');
                        waiter.classList.add('open');
                    }, 300);

                    fetchJSONFile(userSelection, function(data){
                        // do something with your data
                        console.log(data);

                        myH2title.classList.add('hidden');
                        waiter.classList.remove('open');

                        window.setTimeout(function(){
                            waiter.style.display = 'none';
                            restartBtn.style.display = 'none';
                            myH2title.textContent = 'Enjoy your coffee!';
                            myH2title.classList.remove('hidden');
                            newOrderBtn.classList.add('open');
                        }, 300);
                    });

                } else{
                    window.setTimeout(function(){
                        waiter.style.display = 'none';
                        myH2title.textContent = 'Bad response...';
                        myH2title.classList.remove('hidden');
                        restartBtn.classList.add('open');
                    }, 300);
                };
            };
        };
    //


    /*
    Gestion du redémarrage
    */
        function restart(){
            document.querySelector('body').classList.remove('open');
            window.setTimeout(function(){
                location.reload();
            }, 500);
        };

        restartBtn.onclick = function(){
            restart();
        };

        newOrderBtn.onclick = function(){
            restart();
        };

        document.getElementById('mainTitle').onclick = function(){
            restart();
        };

    // 

    /*
    Gestion des requêtes serveur
    */
        function fetchJSONFile(path, callback) {
            var httpRequest = new XMLHttpRequest();
            httpRequest.onreadystatechange = function() {
                if (httpRequest.readyState === 4) {
                    if (httpRequest.status === 200) {
                        var data = JSON.parse(httpRequest.responseText);
                        if (callback) callback(data);
                    }
                }
            };
            httpRequest.open('GET', './' + path);
            httpRequest.send(); 
        }
    //
});