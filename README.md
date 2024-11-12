# File-watcher
Тестовое задание для "Конфидент"

# Task description
Реализовать консольное приложение, которое будет контролировать целостность файлов используя механизм inotify. Т.е. запускаем бинарник с параметром командной строки - путь к конфигурационному файлу. В конфигурационном файле - перечень файлов, целостность которых надо контролировать.

Программка после запуска выводит на консоль перечень файлов, которые она прочитала из конфига и статус успешности взятия под контроль. Во время работы она контролирует, что файлы не изменяются. Какого-то ввода от пользователя не предполагается. При детектировании изменения файла программка выводит сообщение на консоль и восстанавливает изменённый файл (из резервной копии, которую сама же и делает). Реализовать используя парадигму ООП. И желательно также руководствоваться принципами из "Чистого когда" Р. Мартина.

# Env 
Собирал на ОС RedOs и Astra, компилятор std 14 

# Description
Определены интерфейсы в директории <i>libs</i>:
- для проверки состояния файлов 
- для восстановления файлов 
- для асинхронных процессов 

В директории <i>src</i> описана внутренняя логика приложения и реализации интерфейсов.
- класс <i>InotifyChecker</i> реализует интерфейс проверки состояния файлов на основе библиотеки <i>"sys/inotify"</i>
- класс <i>LocalDirBackuper</i> реализует интерфейс восстановления файла, путем сохранения их в поддиректории SAVE_DIR = "backup"
- класс <i>Task</i> реализует интерфейс асинхронно процесса, в основном цикле вызывает указатели на интерфейсы классов проверки и восстановления файлов
- функция <i>Configurator</i> парсит данные из конфига и передает их в <i>TaskManager</i>

# Program options 
При запуске программы возможна передача пути до файла конфигурации:
- флаг <i>Task</i> --config_file или -c, по умолчанию "./config.json" 

# Program lifecycle
При запуске программа парсит конфигурационный json файл в котором определены пути до файлов мониторинга. Затем запускаются процессы/циклы мониторинга файлов, в случае изменения файла, он удаляется и копируется из директории ./backup. При получении сигнала завершения выполнения (SIGTERM, SIGKILL, SIGINT) процессы завершаются и очищаться backup директория. 

# Configuration file 
``` json
{
  "files" : [
    "file1.txt",
    "file2.txt"
  ]
}
```
