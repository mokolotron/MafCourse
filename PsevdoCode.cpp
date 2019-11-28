start(){
    GameManager = new Controller(){
        connect(timer, SIGNAL(timeout()), this, SLOT(printMessages()));
    };
    GameManager->setLinks( якась ссилка на живих юнітів, та інше непонятне )
}

ui."ok"-> maindow.addAmountPlayersButton() -> controller::can_start_new();										
				if( GameFiled :: getInstance()->returnPlayers()->size() > 0)						
					Massage( All old gamers will deleted)					
						if(no) return				
				if(amount < 3 || amount > 18)					//error	
					Massage(" Gamers can be only 3-18")					
					return

                for(int i = 0; i < amount; i++)
                    addPlayers = new Qdialog() {
                            Робим 2 статичні вектори для імен з файлів
                            Заповнюєм рандомними значеннями поля
                        }	
                    addPlayers.exec()  //Показуєм віджет addPlayers
                    ui."okSavePlayer" -> GameField::GetInstance()->addPlayerToGame(імя, стать, вік, ...);
                
                GameManager->refreshTablePlayerStats() //Присвоює вигляду таблиці всі атрибути і плеєра, 
                GameManager->refreshTableGame();       //Обновляет таблицу со статусами игроков

ui."start"-> maindow.startGameButtonPush() 
                GameManager->playGame(){               //Инициализирует step для начала игры
                    this.step = new StartGame(); 
                }
               // підготовка до запуску
                abilityToStartNew = false;
                timer->setInterval(3000);

//  slot  використовує timer при ініціалізації конструктора в satrt() 

timer."onInterval" -> maindow->printMessages() {
    //refresh game window
    QVector<QString> strings =  GameField::GetInstance()->WhatsNext(){
        QVector<QString> strings = step->doWork(); // TODO: подивитися що тут
    }

    if(strings.lenght == 0)
        timer->stop;

    Якщо в  (циклі)  strings.at(i).data()[0] == '~' 
        writeHost->setText(strings.at(i));
    інакше 
        writeChat->setText(strings.at(i));


}


