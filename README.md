# Client

&nbsp;Приложение клиент для записей скидок в таблицу, визуального извещения кассира о статусе (ожидание клиента, ожидание решения кассира) и вывода персональных данных собственника пропуска.



Выполненные действия по улучшению проекта:
- Всё, что не касается работы с диалоговым окном, вынесено в файлы client.h и client.cpp;
- Создан главный класс для взаимодействия с бд - class Client;
- Была предпринята попытка разделения сущностей в объекте 
(отдельно объект бд, объект юзер, объект кассир, статус этого пользователя, объект для хранения вида *текущей* деятельности проги);
- Было выстроено наследование классов (например, пользователь может быть или покупателем или кассиром, некоторые поля для хранения информации у них идентичны) 
<h1><br>PLAN реализации <br></h1>
 <ol><li>заменить по возможности глобальные переменные передачей значений в качестве параметра;
<li>[+]добавить состояния программы
</li> <li>[+]заменить зависимость(переключение) состояния программы от таймеров на зависимость от состояний
</li> <li>[+]добавить какие-то флаги состояния, в зависимости от которых будет меняться поведение программы
</li><li>[+]добавить класс кассир (ФИО, его код подтверждения + код отмены)
</li><li>выводить комментарии блоком над определением
</li><li>упростить методы (по возможности)
</li><li>изолировать реализацию клиента от MFC диалога, оставив возможность вывода данных для пользователя(кассира)
</li> <li>использовать stl библиотеку для работы с текстовыми файлами
 </li><li>решить вопрос с наследованием классов
</li></ol>
<h1><br>PLAN логики<br></h1>
<ul><li>Создать таблицу Discounts в БД;
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[TabNumber] [varchar](255) NOT NULL,
	[EventTime] [datetime] NULL,
	[NumberOfFailures] [int] DEFAULT 0</li>
<li>[+]присоединиться к базе ланч
</li><li> [+]получить кейкод свежайшего события, если  он != 524296 или 589833, значит, запрос не обработан, нужно начать обрабатывать
</li><li> [+]сравнить полученное айди с айди в таблице предоставления скидок Discounts
</li><li> [+]если кейкода юзера не существует в эмплоерс, то кинуть отбивку - Получение скидки по этому пропуску невозможно, обратитесь к системному администратору
</li><li> [+]если нет записи в Discounts с таким табельным сегодня то ждать 10 мин до решения кассира
</li><li> [+]если запись уже есть - кинуть отбивку - сегодня уже предоставлялась скидка
</li><li> [+]если 5) и кассир дал положительный ответ, то записать новую строку в таблицу Discounts
</li><li> [+]если 5) и кассир дал отрицательный ответ, то не записывать новую строку в таблицу Discounts,
потому что она или там есть или не нужна по причине - скидка уже использована юзером с этим табельным или такого табельного вообще нет
</li><li> [~]по каждому отрицательному событию выводить в лог информацию</li></ul>
<h1><br>Известные проблемы:<br></h1>
<ol><li>При потере соединения с локальной сетью будет сыпать ошибками  "Ошибка связи", при запуске без интернета просто закроется (штатно)
</li><li>Почему-то между получением положительного кода и записью в бд происходит задержка в ~3 секунды, например:
<br>информация в лог-файле - 
<br>EXECUTING... (...)(14067, '2022-12-15 15:26:49.000') // localtime: 15:26:49 Четверг 15/12/2022
<br>Информация в лог-таблице кодов - 
<br>ID	EventID	EventTime	KeyCode
<br>70385	70642	2022-12-15 15:26:46.000	524296
<br>70384	70641	2022-12-15 15:26:43.000	14067
<br>Может быть, операции поиска табельного, даты и загрузка пользовательских ПД в программе медленные
</li><li>[РЕШЕНО] AppMsg - Warning: ODBC Success With Info, d:\a01\_work\6\s\src\vctools\VC7Libs\Ship\ATLMFC\Src\MFC\dbcore.cpp(174) : AppMsg - Недопустимый атрибут строки соединения
</li><li>Возможно где-то есть утечки памяти (но это не точно)
</li><li>нужно реализовать загрузку фото сотрудника по табельному в форму без сохранения jpg на накопителе
</li><li>[РЕШЕНО] при непоследовательном и нелогичном вводе кодов программа перестает работать корректно (нужна отладка)
</li><li>необходима переработка архитектуры
</li><li>[РЕШЕНО] Если пользователя не существует, то запись все равно внести можно, а вот удалить ее - нет.
	с существующими пользователями такой проблемы нет

</li><li> Если в конфиге неправильно указаны данные для подключения, то программа уходит в цикл, притом выводя в лог - Ошибка подключения к базе данных. Обратитесь к системному администратору




</ol>
	