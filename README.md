# ClickPad

Petit programme qui permet de clicker comme un malade.  
Choix de la vitesse et du bouton de la souris.  
Pratique dans certain jeux :)

## Hardware

- ATMega 32U4 Pro Micro
- Ecran OLD SSD1306
- Clavier matricielle 4x4



![ClickPad](https://github.com/ttassain/ClickPad/blob/main/blob/clickpad.jpg?raw=true)

## Cablage

### Clavier à matrice 4x4

| GPIO | Clavier |
| --- | ----------- |
| 6 | Column 1 |
| 7 | Column 2 |
| 8 | Column 3 |
| 9 | Column 4 |
| 10 | Row 1 |
| 16 | Row 2 |
| 14 | Row 3 |
| 15 | Row 4 |

### Ecran OLED SSD1306

| GPIO | Ecran |
| --- | ----------- |
| 2 | SDA |
| 3 | SCK |
| RAW | VDD |
| GND | GND |


## Author

TASSAIN Thierry

## License

ClickPad is licensed under the Apache v2 License. See the LICENSE file for more info.