# overnet-client
Простой клиент для подключению к севреру Overnet.

## Подготовка к запуску
После клонирования проекта на локальную машину, откройте его в Visual Studio 2017.
В верхней панели, рядом с кнопкой **Локальный отладчик Windows** убедитесь в сборке Debug **x64** (по-умолчанию стоит x86).

Откройте свойства проекта, перейдите в раздел С/С++ -> Препроцессор.
В поле *Определения препроцессора* добавляем знак ; и пишем следующую строку: **_CRT_SECURE_NO_WARNINGS**, далее просто жмем Применить и ОК.


## Первый запуск
Запускаем программу через Локальный отладчик Windows.
Ждем выполнения программы и сообщения о том, что все тесты закончены. После этого **убеждаемся**, что нет логов вида **[MsgPackTest] FAILED TEST #**.
Если тесты прошли успешно, переходим к шагу Соединение с сервером.

## Соединение с сервером
Первым делом закомментируйте ненужный тестирующий код.
```C
/*
MsgPackTest tester;
tester.Integer_13_13Returned();
tester.Double_1337_1337Returned();
tester.Char_CharReturned();
tester.Array2x4_Array2x4Returned();
tester.Array3x2DobuleInt();
tester.Array4x2_Array4x2Returned();
tester.End();
*/
```
Затем, раскомментируем код, который отвечает за подключению к серверу.
```C
// Connect to server
Uncomment the code below after [Tests]
Client client("18.196.4.216", 2000);
client.Run(onMessageReceived);
```
Выполняем сборку и запускаем приложение.
Сообщение об удачном подключении к серверу выглядит следующим образом:
```Shell
[OVERNET] Received 108 bytes.
[OVERNET] Full message size is 108 bytes.
[OVERNET] Left to receive 0 bytes.
Received message type is [0].

************************
** Welcome to Overnet **
************************
Waiting for 1 clients.
```
```
