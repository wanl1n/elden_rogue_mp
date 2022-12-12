player questline = null;

->enter quest screen

initialize quest
pQuest = createQuestline(TWINKLE_TOES);
pQuest = createQuestline(SWIFT_BROIL);

line = 1;
quest = inactive;

>>> scan input 0, 1

if 1, line = 2;
if 0, line = 3; back to roundtable;

>>> scan input 0, 1

if 1, line = 4; quest = in prog;
if 0, line = 5; back to roundtable;

>>> scan input 0

back to roundtable;


stage 1 in progress  * * * * * * * * * * *


if quest objective = in progress, quest = in prog;
line = 6;

>>> scan input 0, back to roundtable;

if quest objective = done, quest = completed; 
runes + 100;

initiate second stage;

line = 7;

>>> scan input 0, 1

if 1, line = 8;
if 0, line = 9; back to roundtable;

>>> scan input 0, 1

if 1, line = 10; quest = in prog;
if 0, line = 11; back to roundtable;

>>> scan input 0

back to roundtable;


stage 2 in progress  * * * * * * * * * * *

if quest objective = in progress, quest = in prog;
line = 12;

>>> scan input 0, back to roundtable;

if quest objective = done, quest = completed; 
runes + 200;

initiate third stage;

line = 13;

>>> scan input 0, 1

if 1, line = 14;
if 0, line = 15; back to roundtable;

>>> scan input 0, 1

if 1, line = 16; quest = in prog;
if 0, line = 17; back to roundtable;

>>> scan input 0

back to roundtable;


stage 3 in progress  * * * * * * * * * * *

if quest objective = in progress, quest = in prog;
line = 18;

>>> scan input 0, back to roundtable;

if quest objective = done, quest = completed;
line = 19;

addweapon(swift slipper);

>>> scan input 0, back to roundtable;