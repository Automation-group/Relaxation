# Описание
Программа предназначена для микроконтроллера ATmega328P
управляющего БУШД ND1182.

# Сигланы
PUL  - число шагов (срабатывает только по переднему фронту)
DIR - направление вращения двигателя
ENA - вкл./выкл. шаговый двигатель
FAULT - сигнал о неисправности (у БУШД ND1182 этот
сигнал является инвертированным сигналом ENA и
по этому не используется)

Кроме этого обрабатываются сигналы от двух конечных выключателя (верхний и нижний)
и сигнал о перегрузке от блока работающего с тензодатчиком.
