# Игровой руль для ПК на Arduino
* [Описание проекта](#chapter-0)
* [Папки проекта](#chapter-1)
* [Схемы подключения](#chapter-2)
* [Как скачать и прошить](#chapter-3)
* [FAQ](#chapter-4)

<a id="chapter-0"></a>
## Описание проекта
Руль для компьютера + педали на базе Arduino Pro Micro (ATmega 32U4)
   
#### Особенности:
- Потенциометр для определения положения руля
- Сервопривод для обратной связи
- Сервопривод и потенциометр на зубчатой передаче
- Педали-потенциометры
- Функция калибровки

<a id="chapter-1"></a>
## Папки
- **3D** - 3D модели
- **feedbacks** - отзывы
- **firmware** - прошивки для Arduino
- **libraries** - библиотеки проекта. Заменить имеющиеся версии
- **schemes** - схема подключения компонентов + логика управления

<a id="chapter-2"></a>
## Схемы
- Логика управления
  
![SCHEME](https://github.com/Sasha-kife/Computer-wheel/blob/main/schemes/diagram.png)
- Схема подключения №1
  
![SCHEME](https://github.com/Sasha-kife/Computer-wheel/blob/main/schemes/scheme1.jpg)
- Схема подключения №2

![SCHEME](https://github.com/Sasha-kife/Computer-wheel/blob/main/schemes/scheme2.jpg)

<a id="chapter-3"></a>
## Как скачать и прошить
* [Первые шаги с Arduino](http://alexgyver.ru/arduino-first/) - ультра подробная статья **(не моя)** по началу работы с Ардуино, ознакомиться первым делом!
* Скачать архив с проектом
> На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**
* Установить библиотеки в  
`C:\Program Files (x86)\Arduino\libraries\` (Windows x64)  
`C:\Program Files\Arduino\libraries\` (Windows x86)
* **Подключить внешнее питание 5 Вольт** (можно брать от USB компьютера, но может бахнуть)
* Подключить Ардуино к компьютеру
* Запустить файл прошивки (который имеет расширение .ino)
* Настроить IDE (COM порт, модель Arduino, как в статье выше)
* Настроить что нужно по проекту
* Нажать загрузить
* Пользоваться
> Для первоначальной настройки или калибровки надо сначала залить прошивку ["First_setup_or_recalibration"](https://github.com/Sasha-kife/Computer-wheel/blob/main/firmware/First_setup_or_recalibration/First_setup_or_recalibration.ino), и, затем, основную прошивку ["Wheel_v1"](https://github.com/Sasha-kife/Computer-wheel/blob/main/firmware/Wheel_v1/Wheel_v1.ino) или ["Wheel_v2"](https://github.com/Sasha-kife/Computer-wheel/blob/main/firmware/Wheel_v2/Wheel_v2.ino).

## Настройки в коде
    bool debug = 0;     // Режим отладки (1 - вкл, 0 - выкл)
	
<a id="chapter-4"></a>
## FAQ
### Основные вопросы
Q: Как скачать с этого грёбаного сайта?  
A: На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**

Q: Скачался какой то файл .zip, куда его теперь?  
A: Это архив. Можно открыть стандартными средствами Windows, но думаю у всех на компьютере установлен WinRAR, архив нужно правой кнопкой и извлечь.

Q: Комп не сгорит?  
A: Не должен, но не гарантирую)
