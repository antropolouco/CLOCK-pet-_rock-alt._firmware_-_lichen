# pet _rock alt._firmware_-_lichen
 a mayan calendar clock that has some fun treats

2208242305

this was originally an idea for an alt. firmware for jonah senzel's 'pet rick' eurorack module but amy well evolve into an entirely independent module of it's won right or simply a curiosoty of code that ends up totally unrelated whatsoever.

in detaai it's a clock that counts according to the mayan calendar from days up to the 5 x count of long rounds that makes up the precession of the earth count and is somethign like 9,000,000 years long. it has accounting for every damn quirk of the ((20 x 10)+5) day sound of one month set which has 19 day names an conversely the 13 day names which connect to the 20mday month of the other basic calendar round as wel as the 1, xx, 20, 20, 240, 360, 1440, 7800, 20,400, etc. cycles of the greater calnedar ccyles.

not only do i plan this clock to count real time in mayan calendar days n months etc. but also to amrk each and every weird important day of ceremony or festival or w/e i can identify to provide lots of fodder for weirder outputs on said days. i had biggest trouble if anything thinking about the display when realising the pet rock dispaly is very limited and if i had my own choice of display i would at least go for an 8x8 led matrix if not bigger llowing at least the mayan glyphs for 0-19 to  be countd ad infinitum tho preferablysomething better to display thae actual whole calculated mayan date would be fun.

i also thought about various ways to exprress the count as an output - the best of which so far being to clock a cellualr automaton the output of whihc is then 'plotted' as x/y coordinates at to outputs as per the moon outs giving two clocke outs on the pet rock but synced differently. this lead to some investigation into cellualr automata which led to, after i read a paper on biological statistics and probabilities, the invention of a possibly entirely new cellular automaton based on the bayesian entropy fucntion#1

tho that discovery spurred me on to think about mdules featuring all of the amphichiral ca wolfram lists so as to allow the user to scroll through a real neat list of a ton of dif cas to play with and had some fun coming up with neat mathematical ways to compress that dtat storing all those cas on one tiny bit of code, i decided that really is another project entirely and forked off into mutliple project brsnches.

code
the ardunio environment that the module runs on is baically a Clanguage so i threw togther most of it in C++ but there is alo some python for other bits not yet thught through.

further, much of the code for pet rock will stay identical since ts only certain aspects of surface day coutning that have more to do with calnedar name than anything and a bit of display driving that's really gonna change.

the code itself will be exeedingly compact and probably only a few hundred lines total - this is intended to be a lightwieight and compact project and really not that advanced or complex.

dependencies
- the Python code snips will require a bunch of dif libraries but the at's pretty mcuh it - not a lot of external files needed at all really for the most part
- there is hwoever an absolute wealth of info to learnabout the mayan calendar/clock and it's weirdnesses.
- i guess there's a whole buncha arduino drivers and things to pack the code down onto the chip adn turn it into a compaitble firmware etc. but they'll come along later - it's early days yet!

