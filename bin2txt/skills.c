#include "global.h"

#define FILE_PREFIX "skills"
#define NAME_PREFIX "sk"

/*
SKILLS.TXT FILE GUIDE
by Nepharius


Skills.txt, for a long period of time (1.00 until 1.09) was a pretty small file with only a few things to alter (this was mainly limited to the animation used, the parameters passed to the skill and the damage done by the skill), the rest was completely 
hardcoded. How the skills themselves work is still hardcoded (the skill functions), but all other aspects of their behaviour can now be controlled via skills.txt, including which skills access which functions. The file is vast, by far the largest and 
most complex in Diablo II, it contains 256 columns, the maximum supported by M$ Excel. The purpose of this fileguide is not to provide a 100% accurate description of each column, as this is impossible (because how some columns are used depends foremost 
on the skill function accessing them!), it will also not deal with formulae, Xeno wrote a comprehensive guide about the formulae used by the D2 parsing engine, and there is no point repeating this here.



GENERAL SKILL SETTINGS


skill: the ID pointer used to reference this skill within CharStats.txt, Missiles.txt and Monstats.txt, SkillDesc.txt, it is also used within Skills.txt itself. This ID pointer can also be used within AutoMagic, Gems, MagicPrefix, MagicSuffix, MonProp, 
QualityItems, Runes, SetItems, Sets and UniqueItems.txt, however the parsing mechanism used for those files is bugged, and skill names with a space will more often then not fail to work properly (just because Blizzard can do it that way doesn't mean we 
can!). I recommended to use the actual ID numbers rather then the ID pointer in those files. Warning Never use the same ID pointer twice, all skills but the first will be ignored if they have the same pointer!

Id: the actual ID number of the skill, this is what the pointer actually points at, this must be a unique number, the game supports 32767 skills, but you won't be able to use them in conjunction with items, unless you modify ItemStatCost.txt, encoded 
stats (chance to cast level xxx yyy on zzz, and charges) can only store IDs up to 1023, no matter what. Warning Some IDs are referenced by the code (such as aurae used by bosses), you should thus refrain from randomly moving skills around inside the 
file unless you know what you're doing.

charclass: to what character class is this skill assigned, this controls mainly from what DC6 icon library the skill icons are picked and by what bonus stat the skill is going to be effected (+to all Amazon skills etc). Warning All characters must have 
the same amount of skills assigned to them, otherwise only the class(es) with the highest amount of skills will be able to enter games (since the game is preparing the save file for each class for xxx skills, thus those with less then xxx skills will be 
treated as if their save files are corrupted. To solve this problem just add a number of dummy skills to that class (which will not appear on the skill tree or be useable in any way). Leaving this column blank means that the skill has not been assigned 
to any class.

skilldesc: ID pointer from SkillDesc.txt, this controls all the user interface related aspectes of the skill such as the skill icon used, the text displayed in the skill description and how/if the damage and attack rating is displayed on the character 
screen. Warning Never use two identical entries for the same skill if they are assigned to the same character class, unless of course you enjoy crashing.




SERVER-SIDE SKILL FUNCTIONS


These functions where originally referenced by a hardcoded table during 1.00-1.09, as of 1.10 this function index has been softcoded and can now be modified by editing skills.txt, this is the heart and soul of a skill, almost everything that makes a 
skill differ from the others is controlled by the functions used. The functions control but are not limited to: whenever the skill can apply a state or not, whenever the calc columns are used, whenever a parameter is referenced by code directly, whenever
, and how, a missile is launched and anything else you can think of.

srvstfunc: Server starting function, this controls the server side function executed when you rightclick or shift+leftclick somewhere while the skill is assigned to a button.

srvdofunc: Server finishing function, this controls the server side function executed when the starting function finishes executing, it might either be called repeatedly as long as the mouse button remains down, or it may be called periodically (for 
skills like paladin auras and blade shield).

prgstack: Boolean used by charge-up skills, true means the individual charges will stack (Fists of Fire, Claws of Thunder and Blades of Ice), false will make each new charge replace the previous one (Phoenix Strike etc). And indeed, you can make all 
three charges of Phoenix Strike occur at the same time by setting it to true icon_wink.gif

srvprgfunc1: Server side function to execute when releasing (using a finishing move) charge number 1.

srvprgfunc2: Server side function to execute when releasing (using a finishing move) charge number 2.

srvprgfunc3: Server side function to execute when releasing (using a finishing move) charge number 3.

prgcalc1: Calculation used by the server side function of charge number 1 (this column is also used by Shock Web and Blade Fury because the skill functions of those skills access it!).

prgcalc2: Calculation used by the server side function of charge number 2.

prgcalc3: Calculation used by the server side function of charge number 3.

prgdam: Related to the heavily hardcoded progressive stats. 1 is to be used in conjunction with PROGRESSIVE_DAMAGE, 2 is to be used in conjunction with PROGRESSIVE_STEAL, 3 is to be used with the unused PROGRESSIVE_OTHER stat and 4 is to be used with 
PROGRESSIVE_ stats. I have yet to do research on this, but adding new progressive stats would involde expanding the list of functions linked to by this field!



SERVER-SIDE MISSILE SETTINGS


These columns control the various aspects the missiles launched by this skill server side, that is, this is independant from what the player (client) sees on the screen, thus the client-side missile settings must match this to avoid weird behaviour and 
stupid questions from users. But you don't have to make the functions match, nothing will happen if they don't, the missile will just not appear, or appear the way it should, on screen.

srvmissile: Primary missile to launch when the server side starting function is executed. This is launched independant of the server side starting function involved (even when no function is execute at all: see fireball and firebolt for example).

decquant: A boolean that controls whenever this skill will decrease stack or ammunition each time the starting function is executed (this is disabled for strafe, enabling it will make strafe waste as many arrows as you fire).

lob: Another boolean, when enabled the missiles fire will be lobbed (tossed like a grenade). A lobbed missile will vanish (collide with the ground) at the location you clicked with the mouse. Warning A lobbed missile only 'appears' to fly in an arc, 
that is it will still damage everything it would damage if it wasen't lobbed, to make it behave properly the missile being lobbed must be modified (see Missiles.txt fileguide).

srvmissilea: First secondary server-side missile (how and if this is accessed depends on the server side functions used by the skill).

srvmissileb: Second secondary server-side missile (how and if this is accessed depends on the server side functions used by the skill).

srvmissilec: Third secondary server-side missile (how and if this is accessed depends on the server side functions used by the skill).



SERVER CONTROLLED OVERLAYS


srvoverlay: Overlays are usually controlled by client-side code, however mission-critical overlays are handled by the server-side code. This usually applies to those overlays applied to a targeted units when the server-side finishing function executes. 
Mission critical overlays are those used by melee attacks, various monster buffs/curses and by Fist of the Heavens (the downward moving missile is actually an overlay). This is an ID pointer from Overlays.txt. Whenever this is used depends on the server-
side finishing function used.



AURA / CURSE / BUFF RELATED SETTINGS


These columns don't necessarily have to be used by an aura / curse / buff at all - for example, the game also uses these fields for skills that have some sort of search radius or an AoE.

aurafilter: This is a binary filter that controls what type of unit is effected by this skill, a discussion on how aurafilters work can be found here. Not all aura filters will work properly with all skills, it largely depends how the server side skill 
functions search for potential targets! This is used by most skills that search for targets.


0001000010110000011 - inner sight, taunt

0001100010110000011 - slow missiles

0001010010110000011 - lightning fury, conviction, tornado

0001000011110000011 - static field

0000000000000000011 - amplify damage, weaken, iron maiden, life tap, decrepify, lower resist [work on bosses]
0000000000000000010 - dim vision, terror, confuse, attract, grim ward [don't work on bosses]
0010010000000000011 - might, prayer, resist fire, thorns, defiance, resist cold, blessed aim, cleansing, resist lightning, concentration, vigor, fanaticism, salvation, defense curse, blood mana

0001010011110000011 - holy fire, holy shock, hurricane

1001010001010000011 - holy freeze

0001110011110000110 - sanctuary

0001010010110000111 - fist of the heavens

0000001000100000010 - redemption

1100000000000000000 - battle cry

0001110000000000011 - cloak of shadows

0001000001110000011 - mind blast, blade shield

0001000011100001011 - blades of ice

0010000000100000011 - spirit of barbs aura, heart of wolverine aura, oak sage aura


aurastate: The state being applied to the caster (user) of the aura / buff / curse. In the case of enchant this is applied to whatever unit the skill is cast on. This is an ID pointer from States.txt. Warning You shouldn't use the same state on more 
then one skill if both skills are available to the same character or monster, the game uses an index table to determine which state (and thus which stat changes) are currently active on the unit, a state currently present on a unit cannot be applied to 
it again while the first state is present, thus two skills using the same state will never be able to apply at the same time. This does not mean they will always prevent stacking, it means that you will experience the strangest of glitches.

auratargetstate: The state being applied to the reciever of the aura / buff / curse. This is an ID pointer from States.txt. Warning Never use the same state here as you can never know whenever two skills with the same state will be applied to the same 
unit, the game uses an index table to determine which state (and thus which stat changes) are currently active on the unit, a state currently present on a unit cannot be applied to it again while the first state is present, thus two skills using the 
same state will never be able to apply at the same time. This does not mean they will always prevent stacking, it means that you will experience the strangest of glitches.

auralencalc: This field can either contain a calculation or a static value, it controls how long (in frames) the effects of the aura / buff / curse will last. Real auras dont use this, because they are refreshed periodically.

aurarangecalc: This field can either contain a calculation or a static value, it controls the area of effect (in subtiles) in which the aura / buff / curse will effect other units. Some other types of skills also use this (such as Lightning Fury) to 
determine the search radius or damage radius of the missiles released by them.

aurastat1-6: The stats this aura / buff / curse can alter. It contains ID pointers from ItemStatCost.txt.

aurastatcalc1-6: The amount to add or subtract from the stat in question. This field is limited to values between -2147483647 and +2147483647. Higher or lower values will roll.

auraevent1-3: This field specifies what events the aura / curse / buff should react to when this event occurs to the caster (user) of the skill. This is an ID pointer from Events.txt.

auraeventfunc1-3: This field specifies the function to execute when the coresponding event occurs (like the above, this refers to the caster of the skill only). A list of event functions can be found here. Warning The majority of these functions will 
not work properly when called by a skill.

auratgtevent: Not used by vanilla. Warning I couldn't get this to work properly in my tests, but as far as I can say, this is the equivalent to the auraevent columns, but for the reciever of the aura.

auratgteventfunc: Not used by vanilla. Warning I couldn't get this to work properly in my tests, but as far as I can say, this is the equivalent to the auraeventfunc columns, but for the reciever of the aura.




PASSIVE SKILL SETTINGS


Whenever a skill is a true passive or not depends whenever the Passive boolean is switched to true, otherwise the behaviour of these columns depends on the server side skill functions used, they might function as a secondary passive bonus granted by the 
skill, as an extension of the Aura / Curse / Buff columns or applied to a summoned creature.

passivestate: The state used by the game to assign the stats and events related things granted by this passive to the unit. This is an ID Pointer from States.txt. Warning You shouldn't use the same state on more then one skill if both skills are 
available to the same character or monster, the game uses an index table to determine which state (and thus which stat changes) are currently active on the unit, a state currently present on a unit cannot be applied to it again while the first state is 
present, thus two skills using the same state will never be able to apply at the same time. This does not mean they will always prevent stacking, it means that you will experience the strangest of glitches.

passiveitype: This field is used in conjunction with the passive stats used by weapon masteries, they contain an ID pointer to ItemTypes.txt which tells the game what item types will recieve a bonus from the coresponding passive stat. Warning This does 
not work with stats that aren't meant to be part of weapon masteries, forget about it, the only stats this works with are passive_weaponblock and passive_mastery__, period.. Weapon masteries are no hardcoded to the lines in Skills.txt, this has been a 
die hard rumor.

passivestat1-5: This field tells the game which stats are assigned by this passive skill. This contains an ID pointer from ItemStatCost.txt.

passivecalc1-5: This field can either contain a static value or a caltulation telling the game how much to add or subtract from the associated stat. This field is limited to values between -2147483647 and +2147483647. Higher or lower values will roll.

passivevent: Not used by vanilla. Warning I couldn't get this to work properly in my tests, but as far as I can say, this will control what event this passive will react to.

passiveeventfunc: Not used by vanilla. Warning I couldn't get this to work properly in my tests, but as far as I can say, this field controls what function to execute if the associated event occurs.




SUMMON SETTINGS


Special stats added to a summoned creature are either appended via MonEquip.txt, MonProp.txt or via the aurastat or passivestat columns.

summon: This field specifies what creature is summoned by this skill. This is an ID Pointer from MonStats.txt.

pettype: This controls what group the summoned creature is placed in. This controls what icon appears, whenever this summon can co-exist with other summons or not (such as there being only 1 golem, rather then one golem of each type), warping behaviour 
and more. This is an ID Pointer from PetTypes.txt.

petmax: This field can contain either a static value or a calculation which controlls how many summons of this group a player can have at a time. Leaving it blank means there is no limitation.

summode: The animation mode that the summoned creature will play when you summon it. Lets say you want to summon a Zombie, and it should look as if the Zombie crawls out of the soil, then you'd set this to S1 (the special animation of the Zombie). 
Usually you'd use NU (neutral) mode here, because most units won't have animations suitable for this.

sumskill1-5: These fields control the skills that are assigned to the summoned creature. This doesn't meant the summon will use these skills. This is mostly used to pass a synergy bonus to the summoned creature (such as additional damage for Hydra). 
Whenever a summon will actively use any of these skills depends on the AI used. You can forget using the Necropet AI, this AI is totally hardcoded and will not use these skills unless the code is modified. The best AI to use is the Shadowmaster AI, be 
aware that the skills that the summon should use must also be referenced in MonStats.txt. More on how to properly use the Shadowmaster AI can be found here.

sumsk1-5calc: These fields can contain either a static value or a calculation that tells the game what sLvl to assign to the coresponding skill assigned to the summoned creature.

sumumod: This field is pretty neat, it controls what boss modifiers to grant the summoned creature, this means you can make grant your summons properties like Lightning Enchanted or Aura Enchanted (random aura). This column contains ID numbers from 
MonUMod.txt. There is only one minor side effect, because the summoned creature doesn't have a special boss seed, the name that is displayed when you hover over it with Unsummon will be Mind Maw the Slasher.

sumoverlay: This field controls what graphical overlay to display when the creature is summoned (this overlay is applied to the summoned creature, not the caster). This is an ID Pointer from Overlays.txt.





SOUND and OVERLAY SETTINGS


Quite obviously all columns ending with 'sound' are meant for ID pointers from
Sounds.txt whereas those ending with 'overlay' are meant for ID pointers from Overlays.txt.

stsuccessonly: A boolean that controls whenever the assigned sounds and overlays will keep playing even when the casting of the skill is interrupted by an attack landed on the caster. Correction by brappy

stsound: This field controls what sound will be played when the starting function of the skill executes, it will play irregardless of the character class using the skill.

stsoundclass: This field controls what sound will be played when the starting function of the skill executes, it will play only for the character class this skill is assigned to in the charclass column. This is useful for preventing grunts from one 
class to be played when another class uses it (this wasen't the case prior to 1.10, so if you gave Bash to lets say a Sorceress, she would play the Barbarian grunt wavs).

stsounddelay: Boolean of unknown functionality. Warning Again, I couldn't see a difference in-game while testing. But I believe this controls whenever the sound should start playing at the moment the starting function beings execution (false) or when 
the function finishes executing (true).

weaponsnd: This boolean controls whenever or not to play the sound associated with the weapon you have equipped when using this skill when the starting function executes.

dosound: This field controls which sound to play every time the finishing function executes (for a skill like Zeal this would mean every time your Paladin swings at an enemy).

dosound a: How this and the next field work is depending on which finishing functions are associated with the skill. It ranges from specific sounds to play after the attack, to the sounds associated with summoned creatures.

dosound b: How this and the previous field work is depending on which finishing functions are associated with the skill. It ranges from specific sounds to play after the attack, to the sounds associated with summoned creatures.

tgtoverlay: This field controls what overlay to associate with the unit targeted by the skill, this overlay is drawn once the finishing function executes. In the case of Zeal this would mean that the initial swipe will not draw an overlay over the 
monster you attack, but all following swipes will.

tgtsound: This field controls what sound to play (originating from the targeted unit) once the finishing function associated with the skill executes. In the case of Zeal this would mean that the initial swipe will not play a sound but all following 
swipes will.

prgoverlay: How this field is used depends on the skill functions associated with the skill. In the case of charge-up skills, this field contains the first overlay for the charge-up graphics group used by this skill. For other other skills like 
Hurricane it controls what overlay to display while the skill is active.

prgsound: Like the previous field, the way this field works varies with the functions used. It can contain the sounds to play for each charge-up or the sounds to play while a skill like Hurricane is active.

castoverlay: This field controls what overlay to associate with the unit using the skill. This overlay is drawn when the skill is successfully started (the starting function begins to execute - this does not mean the skill succeeds, it only means that 
the code for the skill starts executing).

cltoverlaya: Usually this will work like the previous field, but depending on the skill functions used (such as those of the Sorceress' cold armors) this can vary greatly.

cltoverlayb: Usually this will work like castoverlay, but depending on the skill functions used (such as those of the Sorceress' cold armors) this can vary greatly.





CLIENT-SIDE SKILL FUNCTIONS


These functions where originally referenced by a hardcoded table during 1.00-1.09, as of 1.10 this function index has been softcoded and can now be modified by editing skills.txt. The client side functions handle how the skill will appear on the users 
screen, you should stick with the client/server function pairs Blizzard have used (the skill will otherwise do something completely different from what is shown on screen, which can lead to desync and possibly crashes if the client isn't updated 
properly in MP games), but feel free to experiment.

cltstfunc: Client starting function, This controls the client side function executed when you rightclick or shift+leftclick somewhere while the skill is assigned to a button.

cltdofunc: Client finishing function, this controls the client side function executed when the starting function finishes executing, it might either be called repeatedly as long as the mouse button remains down, or it may be called periodically (for 
skills like paladin auras and blade shield).

cltprgfunc1: Client side function to execute when releasing (using a finishing move) charge number 1.

cltprgfunc2: Client side function to execute when releasing (using a finishing move) charge number 2.

cltprgfunc3: Client side function to execute when releasing (using a finishing move) charge number 3.



CLIENT-SIDE MISSILE SETTINGS


These columns control the various aspects the missiles launched by this skill client side, that is, this is independant from what the server-side code does, thus the server-side missile settings must match this to avoid weird behaviour and stupid 
questions from users. But you don't have to make the functions match, nothing will happen if they don't, the missile will just not appear, or appear the way it should, on screen.

cltmissile: Primary missile to launch when the client side starting function is executed. This is launched independant of the client side starting function involved (even when no function is execute at all: see fireball and firebolt for example).

cltmissilea: First secondary client-side missile (how and if this is accessed depends on the client side functions used by the skill).

cltmissileb: Second secondary client-side missile (how and if this is accessed depends on the client side functions used by the skill).

cltmissilec: Third secondary client-side missile (how and if this is accessed depends on the client side functions used by the skill).

cltmissiled: Fourth secondary client-side missile (how and if this is accessed depends on the client side functions used by the skill).




CLIENT-SIDE SKILL CALCULATIONS


cltcalc1-3: These fields serve special purposes and are referenced by the client side skill functions, what they do depends entirely on the functions involved. You reference them inside other calculations if you wish or require additional space for a 
very long formula (but you should make sure the functions used don't actually access these fields first!). They can of course also contain a static value instead of a calculation.



MISCELLANEOUS SETTINGS I


warp: A boolean of unknown function. Warning Set to true only for skills that shift you to another spot, but altering this seams to have no influence on the game at all. Maybe this has to do with MP games and synchronisation, leave it alone to stay on 
the safe side.

immediate: A boolean that controls whenever an aura will apply immediately after it is assigned to a mouse button or whenever to wait until the first predelay has elapsed. Usually those aurae that grant a bonus to the players stats will be set to true 
herein, while those that effect monsters (like Conviction) will be set to false.

enhanceable: A boolean of unknown function. Warning This is set to true only for skills that are always sLvl 1, nonetheless this doesn't influence if the skill gains any bonus from items, it seams to do nothing noteable (if it does anything at all).

attackrank: This field is related to how monsters react when the skill in question is used against them. Ever wondered why monsters don't attempt to retaliate if they are hit by a elemental damage aura, this field is what controls the retaliation 
behaviour. As a rule of thumb, the higher the more likely a monster will retaliate against the attack. 0 will make them ignore it (like they ignore elemental damage auras).




EQUIPMENT RELATED USAGE RESTRICTIONS


noammo: This boolean controls whenever the player requires ammunition to use this skill. Use this, in conjunction with decquant to make other missile skills behave like Magic Arrow. Obviously setting this to true means no ammo is required icon_wink.gif.

range: This switch field can take one of four values. It controls how the player can launch this skill. First of all, none means it has no restrictions on it, and is a spell (like Fire Ball), rng means this skill is a ranged skill (Javelin skills, Bow/
Crossbow skills), h2h means that this is a Hand to Hand combat skill (melee) (Bash, Sacrifice etc), both means that the skill can function as both h2h and rng (like Attack). Warning Setting a skill to h2h will not prevent the player from launching it 
from afar, he can always shift-click!

weapsel: This field controls how to access the gear necessary to use this skill. A blank value means it wont handle this skill in a special way (that is, it'll look for the weapon in the Right hand of the player). 1 in this field will make it look for a 
weapon in the Left hand of the player. 2 in this field means that it can either use the Right or the Left or Both weapons (used by Whirlwind). 3 in this field means that it will always use Both weapons and finally a value of 4 means that the game will 
not use a weapon, but a piece of armor. Be aware that code 4 is heavily hardcoded and will only work with those skill functions using it in vanilla!

itype1-3: The item type required to use this skill (needed to use this skill, this restriction is imposed on the players right hand). This is a ID pointer from ItemTypes.txt.

etype1-2: The item types this skill cannot be used with (even if they are included in the former fields! This restriction is imposed on the players right hand). This is a ID pointer from ItemTypes.txt. This is why you cannot use Attack with a throwing 
potion for example (you could before LoD).

itypeb1-3: The item type required to use this skill (needed to use this skill, this restriction is imposed on the players left hand). This is a ID pointer from ItemTypes.txt.

etypeb1-2: The item types this skill cannot be used with (even if they are included in the former fields! This restriction is imposed on the players left hand). This is a ID pointer from ItemTypes.txt. This is why you cannot use Attack with a throwing 
potion for example (you could before LoD).



ANIMATION SETTINGS


anim: The animation mode that the game plays when the player uses this skill. The list of animation modes for players can be found within PlrMode.txt. Setting this to mode SQ will make the player use the associated sequence instead. This also controls 
whenever the skill is effected by FCR or IAS! In case of a sequence it depends on what animations are used by the sequence. Warning Certain modes (like GH) will crash the game as they aren't meant to be used by skills.

seqtrans: This field apparently doesn't do anything, it probably was meant to control animation mode played before starting the sequence, but is obviously not used (it never was, not even in 1.00 IIRC).

monanim: Monsters always use the skill mode that you assign in MonStats.txt. The only units that access this field are Shadow Masters and Shadow Warriors, because they use Assassin animations. A list of modes can be found within PlrMode.txt for these 
two summons. If a value of xx is supplied the Shadow's will look for the sequence assigned inside MonStats.txt this workaround was put there by Blizzard because monsters are unable to use Player sequences. New wording in part on a suggestion by Myhrginoc.

seqnum: This field contains the ID of the player-animation-sequence to play when this skill is used in case the anim column is set to use mode SQ. Unlike monster sequences, player sequences are unfortunately still hardcoded in a table within D2Common.dll
. Below is a list of sequences (the proper characters are needed for each sequence, but some work on more then one class).


0 = no sequence (if you use this you'll see half of a casting anim, and then an assertion error)
1 = used by Jab
2 = messed up sequence originally used by Sacrifice (flashes on some weapons)
3 = unused sequence (uses casting anim)
4 = used by Charge
5 = unused sequence (from the times conviction wasen't an aura, the sequence still works on a pally with a sword)
6 = used by Inferno
7 = unused sequence (uses casting anim)
8 = used by Impale
9 = messed up sequence originally used by Fend (doesn't work properly)
10 = used by Whirlwind
11 = used by Double Swing
12 = similar to 6, used by Lightning skills
13 = used by Leap
14 = used by Leap Attack
15 = used by Double Throw
16 = used by Double-Claw attacks
17 = unused Assassin? sequence
18 = used by Arctic Blast
19 = unused sequence originally used by Dragon Talon
20 = unused Assassin? sequence
21 = used by Dragon Flight
22 = unused sequence originally used by Were-transform skills
23 = used by Blade Fury
Sequences >24 but exist in the DLL (the highest confirmed one is 41, but there are likely more).


seqinput: This controls the interval to wait before looping the sequence (used by recursive skills such as Inferno), setting this to 100 will make the game pause between individual inferno bursts for example. This is most likely in milliseconds and not 
frames, setting the interval to a too small value however will cause the sequence to skip the trigger frame (on the client-side only however...)!

durability: A boolean of unknown function. Warning This doesn't have anything to do with skills that can reduce durability. It's apparently related to skills that use sequences however. No idea what it does, follow the Blizzard approach and just use it 
with those skill functions they use it with to be safe of unexpected side effects.

UseAttackRate: A boolean of unknown function. Warning This is not related to Attack Rating if you wonder. The name suggests that it is related to Attack Rate however (which is the stat increased by IAS) however it seams to have no influence whatsoever 
in game, most likely a deprecated leftover from alpha D2 times.




TARGETING CONTROLS


While these columns all look straitforward, they usually aren't. What and whenever a skill can target something depends foremost on the skill functions involved, these columns are just a second layer of minor importance, unfortunately.

LineOfSight: This field seams to be a binary flag switch, but only one flag is used by the game, which is 4 (100). It controls whenever or not the skill takes into account the players Line of Sight. That is, if this is set to 4 you cannot cast the skill 
through walls, but if it is left blank you can. This is easy to test with summoning skills. If for example you'd set this to 0 on a skill like Valkyrie you can summon a valk in a different room, without ever opening the door.

TargetableOnly: A boolean of unknown function. Warning It doesnt do what the name suggests anyhow. Frankly enough it doesn't seam to do anything.

SearchEnemyXY: A boolean of unknown function. Warning This usually comes in conjunction with the previous field, likewise it doesnt seam to do anything (noteable at least).

SearchEnemyNear: A boolean that controls whenever the skill will make other people call you a noob in MP games , I mean whenever it should automatically pick its own targets (this works best with the left button (combined with shift obviously - it doesn'
t need to be an enemy, it can also be a corpse for skills that target corpses), heck the character will even pursues monsters on his own as long as the button is held down!). This worked on all skills I tested it on. Don't abuse this field, it will make 
D2 even easier then it is, as you won't even need to target anything, just hold the button...

SearchOpenXY: When set to true, this boolean will make the skill look for an unoccupied subtile (apparently depending on the size settings of the controllermissile created by the skill) as the target for the skill (this is used by skills like Fire Wall, 
Meteor and Blizzard which create a invisible controller missile), it makes sense because no two units (and missiles ARE units) can occupy the same subtile, so if Fire Wall or a similar skill was to spawn in an occupied subtile the game would either 
crash OR the skill would never show any effect since the missile is destroyed before it triggers. If no free subtile is found in proximity to the target of the skill, the execution of the skill will fail. Confirmed by Brother Laz.

SelectProc: This field is always to be used in conjunction with the following field. It controls which corpses you can target and has 6 different filter lists. 1 is used by the variants of Corpse Explosion, 2 is used by Raise Skeleton and Raise Skeletal 
Mage, 3 is used by Revive, 4 is used by Find Potion, 5 is used by Find Item and 6 is used by Grim Ward. I haven't tested if this works on living monsters (such as making a skill that cannot target bosses). Warning This does not control whenever a skill 
can actually be used on the targeted corpses (you cannot make Revive work on boss-corpses etc), but you will be able to highlight them. Not very useful...

TargetCorpse: This boolean controls whenever the skill can be cast on a corpse (it doesn't control whenever the corpse can be selected, it only controls if the skill is cast on the corpse AFTER it is selected, whenever or not it can select the corpse 
depends on the skill functions and filter list used).

TargetPet: This boolean controls whenever the skill can be cast on a summon or hireling (it doesn't control whenever the summon or hireling can be selected, it only controls if the skill is cast on the summon or hireling AFTER it is selected, whenever 
or not it can select the summons or hirelings depends on the skill functions used).

TargetAlly: This boolean controls whenever the skill can be cast on a other players (it doesn't control whenever the another player can be selected, it only controls if the skill is cast on another player AFTER it is selected, whenever or not it can 
select another player depends on the skill functions used).

TargetItem: This boolean controls whenever the skill can be cast on items lying on the ground (it doesn't control whenever the item can be selected, it only controls if the skill is cast on the item AFTER it is selected, whenever or not it can select an 
item depends on the skill functions used).

TgtPlaceCheck: This boolean is only used by monster resurrection spells. Setting it to false will break those skills (Resurrect and Resurrect2), I don't know what it does other then enabling those skill functions though.



MISCELLANEOUS SETTINGS II


AttackNoMana: A boolean that controls whenever or not the player should perform a regular attack in-case he runs out of mana while using this skill. Correction by Nameless.



ITEM-EVENT RELATED SKILL SETTINGS


These columns only influence the behaviour and looks of a skill when it is launched by a Chance-To-Cast event function, they don't effect the skills normal behaviour. I didn't test most of these because I have no idea how exactly I should see the 
differences as they appear to be minimal, so they are listed as unknown or unclear with my best guess appended.

ItemEffect: Server-side launcher function. This field controls what function is called when this skill is launched by a chance-to-cast modifier. Leaving it blank means no function is called, and the skill isn't cast. You would usually use function 1. 
But there are at least two others (36 and 151). Function 36 will fire the skill from the target rather then the wielder of the item. Additional info supplied by Brother Laz

ItemCltEffect: Client-side launcher function. This is only required if an abnormal launcher function is used in the previous field. Blizzard uses 10 and 96 as equivalents to server-functions 36 and 151.

ItemTarget: A switch of unclear functionality. Warning This seams to be another one of those targeting filters. By default this is blank (0), but for some skills special targeting functions are used. 1 is used by Enchant (which can also be cast on 
nearby allies), 2 is used by Teleport (which picks a random empty subtile), 3 is used by the corpse explosion variants and probably selects a random corpse and 4 is used by homing missiles (Bone Spirit) and Fist of the Heavens (skills that need an 
absolute target).

ItemCheckStart: A boolean of unknown function. Warning I assume that this is used to prevent collisions between the Hydra and Bone Prison who have this switched to true and occupied subtiles before the starting function is execute.

ItemCltCheckStart: A boolean of unknown function. Warning This seams to serve a similar purpose to the one assumed for the previous field, seams to tell the game to check if the server-side starting function has executed successfully before calling the 
client function (used by Corpse Explosion skills, probably to prevent the gore-graphic from showing up even if the skill fails).

ItemCastSound: This controls the sound that is played instead of the regular sound when the skill is launched by an Item Event. This is a ID pointer from Sounds.txt.

ItemCastOverlay: This controls the casting overlay displayed instead of the regular overlay when this skill is launched by an Item Event. This is a ID pointer from Overlays.txt.



POINT PLACEMENT and PRE-REQUIREMENT SETTINGS


skpoints: This field can contain either a static value or a calculation. This controls how many skill points are necessary in order to boost this skill by 1 sLvl.

reqlevel: The minimum character level required in order to put a point in this skill. To remove the hardcoded level requirement from OSkills you can set this to -6.

maxlvl: The maximum sLvl this skill can achieve. Warning The actual absolute maximum skill level is controlled by the MaxLevel row in Experience.txt and is thus always equal to the maximum cLvl of the class using the skill.

reqstr: How much strength the player requires in order to put a point in this skill (first point only). This is functional as it was always, but it isn't displayed on screen.

reqdex: How much dexterity the player requires in order to put a point in this skill (first point only). This is functional as it was always, but it isn't displayed on screen.

reqint: How much energy the player requires in order to put a point in this skill (first point only). This is functional as it was always, but it isn't displayed on screen.

reqvit: How much vitality the player requires in order to put a point in this skill (first point only). This is functional as it was always, but it isn't displayed on screen.

reqskill1-3: These fields contain the ID Pointers (name column) of the other skills you need in order to put your first point in this skill (aka simply the prerequired skills).



STATE RELATED RESTRICTIONS


restrict: This switch field controls under what state (shape in case of a druid) this skill can be used. 0 means that it can only be used while in Human form, 1 means that it can be used both under shifted and under Human form and 2 means that it can 
only be used when in one of the states defined in the three following columns.

state1-3: This field controls which states this skill is restricted to, in the case restrict is set to 2. This is an ID pointer from States.txt.



SKILL DELAY SETTINGS


delay: This field can contain either a static value or a calculation. This controls how many frames the skilldelay state will be applied to the character after using this skill. Among others this also controls which skills will be disable while that 
state is active. Any skill with a value greater then 0 in this column will be disabled while under the influence of the skilldelay state. When the skill delay is applied depends on the skill used, usually they initialize once the trigger frame of the 
animation has triggered an event. The delay counter will be reset should the execution of the skill be interrupted by an attack.



MISCELLANEOUS SETTINGS III


leftskill: A boolean that controls whenever or not you can use this skill will appear on the list of skills you can assign to the left mouse button. Warning A bunch of skills (especially all auras) cannot be used on the left mouse button, no matter what 
you set this to, this is caused by engine limitations, forget about it. You shouldn't put things like curses, summoning and the like in here, it only serves to causes gameplay related annoyance.

repeat: A boolean of unclear functionality. Warning This boolean is used in conjunction with skills that keep repeating their finishing function for as long as you keep the button pressed (Inferno, Arctic Blast, Blade Fury), however unchecking it doesn'
t have any influence on the game, the skills work like they did before, so I'm a bit puzzled regarding the real purpose of this field. Set it to true on clones of those three skills, to prevent possible problems.

checkfunc: This field contains a reference to a slot in a function table of a special function to call, but the purpose is still unknown. Warning This appears to be a sort of callback function to execute once the main skill functions finish executing. 
The game uses function 1 for all skills that can use up ammunition (arrows, bolts), 2 is used for throwing (but not the Amazons javelin skills!), 3 is used for Left Hand Throw, 4 is used for Left Hand Swing, 5 is used for the scroll and book skills (
these aren't skills at all, what they do is controlled solely by the functions assigned in misc.txt and books.txt) and 6 is used by Double Throw. These are most likely related to updating quantity data in multiplayer games from the looks of this.



MANA COST SETTINGS


The following fields control the mana cost of the skill, and how the mana cost is to be applied. In order to not over-complicate the explanations below, here is a formula to calculate mana cost (replace the column names with the values you've put in 
those columns in Skills.txt, obviously). For effectiveshift value see the table below this section.

manacost = max((mana+lvlmana*(sLvl-1))*effectiveshift,minmana);



nocostinstate: A boolean related to the other state-restriction related columns found earlier in the file. This controls whenever or not the skill will require no mana while the player is transformed (shape shifted), this is used to make Werebear and 
Werewolf cost no mana when the Druid is shape shifted, so he can return to human form without any mana cost.

usemanaondo: A boolean that controls when the mana pool is diminished, I can't properly explain this but the following example will demonstrate how it works, this field is usually not noteable, but if you set this to true on a skill like Inferno you 
will only loose mana once you let the button go (even if you cast the Inferno for a whole hour, day, month or year), but once you let the button go and the game finishes executing the functions you get the whole mana cost thrown at you. Warning This 
doesn't always work, sometimes you will not loose any mana, even after you let go of the mouse button, so don't overuse this.

startmana: The minimum amount of mana required to cast this skill. This does not control how much mana the skill uses, but the icon will remain red as long as mana is below this. For example Inferno is not castable by a Sorceress who only has 5 mana. 
This can be quite nasty, see it as if it was called ReqMana. icon_wink.gif

minmana: The mana cost for this skill will never fall below this minimum value. This functions like max(minmana,manacost);, this is useful for skills with decreasing mana cost per sLvl while preventing them from dropping too low.

manashift: This field controls the precision of the mana cost. Mana Cost is handled in 256ths for extra precision (mana is handled in 256ths by code). Internally this is simply a bitwise shift, but for not making this too complicated see the table below 
for multiplies and some other values that will aid you in understanding how it works. The mana cost in the example is 1000. To get the proper mana cost just multiply it by the multiplier I've listed below.


manashift precision multiplier percentage example mana cost
(skills.txt = 1000)
-------------------------------------------------------------------
0 1/256 = 0.00390625 ( 0.390625%) 3.90625
1 2/256 = 0.00781250 ( 0.781250%) 7.8125
2 4/256 = 0.01562500 ( 1.562500%) 15.5625
3 8/256 = 0.03125000 ( 3.125000%) 31.25
4 16/256 = 0.06250000 ( 6.250000%) 62.5
5 32/256 = 0.12500000 ( 12.500000%) 120
6 64/256 = 0.25000000 ( 25.000000%) 250
7 128/256 = 0.50000000 ( 50.000000%) 500
8 256/256 = 1.00000000 (100.000000%) 1000
9 512/256 = 2.00000000 (200.000000%) 2000
(etc)


mana: The base mana cost of this skill at sLvl 1.

lvlmana: The additional mana cost added to the base mana cost with every additional sLvl.



MISCELLANEOUS SETTINGS IV


interrupt: A boolean that controls whenever the player will stop performing this skill should he get hit in the middle of doing so. Warning Since the original release of the game this whole uninterruptable buiseness is bugged beyond belief. You should 
always set this to true. If the player performs an uninterruptable skill and gets hit, he will indeed complete performing the skill, but it will more often then not fail to do any damage (it's only performed on the client!)

InTown: This boolean controls whenever or not this skill can be used inside a town, damage cannot be dealt inside a town, neither will the skill create any missiles, thus you should only use this with buffs and summoning skills. Warning All auras 
whatsoeever must have this set to true, otherwise you'll experience glitches galore.

aura: A boolean that controls whenever this skill is an aura. This controls the color-tint of the skill icon and all other aspects unique to aurae. It is required to access the perdelay column.

periodic: A boolean of similar nature to the previous one. This controls whenever this skill will execute every time the perdelay countdown has elapsed for the time the state assigned to the skill remains active. Currently used by Blade Shield and 
Thunder Storm, experimenting with this could be interesting.

perdelay: This field can either contain a static value or a calculation, this controls the interval used by aura and periodic skills. Auras will be applied to other units every time this interval has elapsed. Periodic skills will execute their code 
every time this interval has elapsed. This is in frames, obviously.

finishing: A boolean that controls whenever this skill can function as a finishing move for charge-up skills. No, setting this to true on a charge-up skill will not work.

passive: A boolean that controls whenever this skill is a passive skill (and thus applies what you've defined in the passive skill at all times). A passive skill will never show up within the left or right skill menus.

progressive: A boolean that controls whenever this skill is a charge-up skill. Setting this to false on a charge-up skill will break it (the charges will just vanish after it is charged up).

general: A boolean of unknown functionality. Warning This boolean is only enabled for skills that are inherited by characters via CharStats.txt. Altering this doesn't seam to change anything noteable in-game.

scroll: A boolean of unknown functionality. Warning This boolean is only enabled for skills that are referenced by Books.txt. Altering this doesn't seam to change anything noteable in-game.




SERVER-SIDE SKILL CALCULATIONS and PARAMETERS


calc1 to calc4: These fields control special calculations accessed directly by the server-side skill functions. Their purpose is universal, as their result will be applied to whatever the function is designed to apply it to. Some missile functions will 
access these fields if the missile is assigned to this skill in Missiles.txt. This obviously can contain calculations (and static value). If a calculation field isn't used by the skill function you can try everything from throwing your computer out of a 
window to yelling at the field, it won't change unless you use another skill function icon_exclaim.gif. You can reference unused skill calculation fields inside other calculation fields however to obtain more space for long formulae.

param1 to param8: These fields contain special parameters either passed on directly to the skill function or referenced within calculations inside this and SkillDesc,txt. Parameters can only contain static values.




MISCELLANEOUS SETTINGS V


InGame: A boolean that controls whenever or not the skill is available in-game. Setting this to false will make the skill noexistant in-game.




ATTACK RATING RELATED SETTINGS


The following columns will are used to grant a bonus to attack rating (the stat that determines your chance to hit a target) for that skill (so for aurae and buffs these columns are useless other then for additional parameters to reference in 
calculations). These columns are bugged, they will not work with missile attacks, that is, the AR bonus is never applied even if it shows on screen. This especially applies to Bow and Crossbow skills. The bonus granted by the column is a percentage, not 
a static bonus. So if the columns give you 100% extra AR that doubles the AR you have while using the skill, it does not add 100 to it.

ToHit: The base bonus to attack rating granted by this skill at sLvl 1.

LevToHit: The additional bonus to attack rating added to the base bonus granted by this skill every sLvl after sLvl 1.

ToHitCalc: A field that can either contain a calculation or a static value that determines the bonus to attack rating granted by this skill, when this is not blank (equals 0) the previous two columns are ignored by the game.



SPECIAL ATTACK SETTINGS


The following fields are still pretty cryptic (except HitClass), they are used to apply special events to successful attacks landed by this skill.

ResultFlags: This field is another binary switch, it controls special events that occur as a result of a successful hit landed by the skill. Below are two reference tables showing which skills/missiles use what and also what the individual binary 
switches do in case I managed to decypher them. To use two switches you add their decimal values together. So to make a switch that has all of them set (111111111111111) you'd add 1+2+4+8+16+32+64+128+256+512+1024+2048+4096+8192+16384 together (equals 
32767), or just pump the binary value into the windows calculator and convert to decimal.

000000000000100 - used by missiles that get destroyed on collision
000000000000101 - telekinesis, diablo run, fire throwing potion missiles
100000000000001 - iron maiden, holy fire, holy freeze, holy shock
000000000001000 - smite, bash, grizzly smite, leap knockback missile, radament holyboly [unused]
000000000001001 - mind blast, hell meteor collision missile
000000000010001 - sanctuary
000000000000001 - rabies, hurricane, siege beast stomp
000000000100000 - blade shield


000000000000001 = 1 - nothing noteable
000000000000010 = 2 - nothing noteable
000000000000100 = 4 - nothing noteable
000000000001000 = 8 - knock back
000000000010000 = 16 - damage a unit without any collision appearing (aka only the life decreases!), probably ignores defense
000000000100000 = 32 - nothing noteable
000000001000000 = 64 - nothing noteable
000000010000000 = 128 - nothing noteable
000000100000000 = 256 - never deal any damage with this attack
000001000000000 = 512 - like 256
000010000000000 = 1024 - nothing noteable
000100000000000 = 2048 - nothing noteable
001000000000000 = 4096 - nothing noteable
010000000000000 = 8192 - nothing noteable
100000000000000 = 16384 - nothing noteable


HitFlags: Pretty much unknown, this is another binary switch (that is barely used on skills). Warning This is used with those skills that have abnormal ways to deal damage and with missiles that radiate their damage on collision, keep with Blizzard's 
settings to avoid glitches.

10 - telekinesis, rabies, hurricane, missiles that carry damage over to their explosion radius


HitClass: Hit classes control the sounds played when a target is successfully hit by the skill or missile. Below is a table of known hitclasses.

2 - throwing axe sound
3 - blade shield sound
6 - javelin collision sound
10 - arrow collision sound
32 - fire scorch sound
48 - cold sound
64 - lightning shock sound
80 - poison sound (gas)
96 - stun sound
109 - telekinesis sound
112 - bash sound
141 - attacker takes damage sound
157 - sanctuary sound
176 - poison sound (liquid)





MISCELLANEOUS SETTINGS VI


Kick: A boolean of unclear purpose. Warning Obviously this is set to true on skills that use the kicking animation, but what exactly it controls I can't say, setting it to true on other skills seams to have no influence on the game.




DAMAGE RELATED SETTINGS


The following columns control how this skill will deal damage, note that many skills also use skill calcs for enhanced damage ontop of this. Below is a more or less accurate formula to calculate the damage done by a skill. For the value of 
effectiveshift see the table at the end of the section.

damage[type] = ((base_damage*srcdamage/128)+(skill_damage*effectiveshift*(100+synergy)/100))*(100+enhancer_stat)/100

base_damage is the damage you would do with a normal attack (this is seperated by element, so consider this whole thing is done for each element involved, including physical damage and lifesteal/manasteal) in addition to any bonus added by damage 
enhancements applied by the skill through calc fields.

skill_damage is the additional offweapon damage granted by the skill (all sLvl boni included here).

enhancer_stat is a stat that increases this damage type as a whole (the 'extra fire damage' style stats).



HitShift: This field controls the precision of the off-weapon damage done by this skill. Damage is handeled in 256ths (life is handled in 256ths by code). Internally this is simply a bitwise shift, but for not making this too complicated see the table 
below for multiplies and some other values that will aid you in understanding how it works. The damage in the example is 1000. To get the proper damage just multiply it by the multiplier I've listed below.


hitshift precision multiplier percentage example damage
(skills.txt = 1000)
-------------------------------------------------------------------
0 1/256 = 0.00390625 ( 0.390625%) 3.90625
1 2/256 = 0.00781250 ( 0.781250%) 7.8125
2 4/256 = 0.01562500 ( 1.562500%) 15.5625
3 8/256 = 0.03125000 ( 3.125000%) 31.25
4 16/256 = 0.06250000 ( 6.250000%) 62.5
5 32/256 = 0.12500000 ( 12.500000%) 120
6 64/256 = 0.25000000 ( 25.000000%) 250
7 128/256 = 0.50000000 ( 50.000000%) 500
8 256/256 = 1.00000000 (100.000000%) 1000
9 512/256 = 2.00000000 (200.000000%) 2000
(etc)


SrcDamage: This field controls how much weapon damage to transfer to the skill. Unlike HitShift this allows for a much greater degree of precision as instead of using the value 8 as the base, it uses the value 128 allowing for 127 different settings! 
Simply remember that 128 equals 100%, 96 equals 75%, 64 equals 50%, 32 equals 25% and so on. So as an example, a character doing 1000-3000 damage with normal attack would do roughlt 515-1547 with a skill having a SrcDamage value of 66. This applies to 
all types of damage done by the character without the skill (and this also includes lifesteal and manasteal, which are damage types). Each damage type is treated seperatly.

MinDam and MaxDam: Controls the basic minimum and maximum physical damage dealt by this skill at sLvl 1. Warning Whenever the game will use these fields depends on the skill functions used. But almost all of them will do.

MinLevDam1 to MinLevDam5 and MaxLevDam1 to MaxLevDam5: Controls the additional physical damage added to the skills minimum and maximum damage for every additional sLvl. LevDam1 is used for sLvls 2-8, LevDam2 for 9-16, LevDam3 for 17-22, LevDam4 for 23-
28 and LevDam5 for sLvls above 28. Warning Whenever the game will use these fields depends on the skill functions used. But almost all of them will do..

DmgSymPerCalc: This field controls the synergy bonus (a percentage) added to the physical damage done by the skill (this does not influence physical damage passed over by SrcDamage). This field can contain both calculations and static values.

EType: Controls the type of elemental damage dealt by this skill (this also controls whenever +to fire skills and similar costum modifiers will effect this skill or not). This is an ID pointer from ElemTypes.txt.

EMin and EMax: Controls the basic minimum and maximum elemental damage dealt by this skill at sLvl 1. Warning Whenever the game will use these fields depends on the skill functions used. But almost all of them will do.

EMinLev1 to EMinLev5 and EMaxLevDam1 to EMaxLevDam5: Controls the additional elemental damage added to the skills minimum and maximum damage for every additional sLvl. LevDam1 is used for sLvls 2-8, LevDam2 for 9-16, LevDam3 for 17-22, LevDam4 for 23-28 
and LevDam5 for sLvls above 28. Warning Whenever the game will use these fields depends on the skill functions used. But almost all of them will do..

EDmgSymPerCalc: This field controls the synergy bonus (a percentage) added to the elemental damage done by the skill (this does not influence elemental damage passed over by SrcDamage). This field can contain both calculations and static values.

ELen: The base duration of the elemental damage used, if this damage type uses duration (stun, pois and burn use duration), this is in frames of course. Burn damage is not fire damage. Warning Whenever the game will use these fields depends on the skill 
functions used. But almost all of them will do..

ELevLen1 to ELevLen5: Controls the additional duration added to the base duration with every sLvl past sLvl 1. LevLen1 is used for sLvls 2-8, LevLen2 is used for sLvls 9-16 and LevLen3 is used for sLvls above 16. Warning Whenever the game will use these 
fields depends on the skill functions used. But almost all of them will do..

ELenSymPerCalc: This field controls the synergy bonus (a percentage) added to the duration of the elemental damage done by the skill (this does not influence duration passed over by SrcDamage). This field can contain both calculations and static values.




AI RELATED SETTINGS


aitype: This controls how the skill will be used by Shadow Masters and Shadow Warriors, and in the case of the Act III Iron Wolves this controls how they use the Sorceress cold-armors. See the following topic for details.

aibonus: This field increases the probability that a Shadow Master will use this skill. See the following topic for details.



ITEM COST RELATED SETTINGS


CostMult: This controls by how much the base price of an item is multiplied if this skill is present on it. Keep it below 1024, higher values are ignored by the game.

CostAdd: This controls the additional amount of gold added to the price of an item for each sLvl of this skill present on the item.

*/

/*
Ilvl = item level //物品等级 
Clvl = character level //角色等级 
Blvl = base level //技能中是 技能基本等级,也就是加点上去的等级 
lvl = skill level //物品叠加后的,技能等级 
lvl = item-out level //输出物品的等级 
//////////////////////////////////////////////// 
所以 Ilvl 和 Clvl 一般出现在合成公式中,用于限制合成物品 
原暗黑->橙色装备,都是有限制的,,只有到级别才能合成好的,Ilvl Clvl 中的30 50应该是占用原物品等级 和 角色等级的白分之30 50的意思, 
Ilvl = 30 Clvl = 50; 放入物品50级,人物 60级 
输出物品上限为 50*0.3+60*0.5 = 45

skill=技能名称；

Id=技能的ID代码；

charclass=哪位角色使用此项技能；

skilldesc=对于技能的说明；

srvstfunc=此列是针对战网所用，校验DLL文件关于技能的描述是否正确；

srvdofunc=此列是针对战网所用，如果校验DLL文件关于技能的描述正确的话，载入角色的相关信息；

prgstack=进程包，说明：关于游戏进程的参考值；

srvprgfunc1,2,3=此列是针对战网所用，服务器根据游戏的进程调整相应角色的攻击功能；

prgcalc1,2,3=“刺客”的技能控制数值；

prgdam=“刺客”所释放的能量技能的伤害值参数；

srvmissile=服务器调控“箭”类的参数（根据missiles.txt）；

decquant=受外界影响所削减的伤害值；

lob=54X:“箭”以直线还是曲线行进；

srvmissilea,b,c=服务器从missile.txt文件中查找“箭”的类型；

srvoverlay=服务器所控制的图像选择参数；

aurafilter=服务器对于“光环”的设定参数；

aurastate=角色在使用“光环”魔法时对于角色名称的影响；

auratargetstate=被动“光环”魔法收益者的角色名称的影响；

auralencalc=“光环”所持续的时间，同Skillcalc.txt文件关联；

aurarangecalc=“光环”影响的范围；

aurastat1-6=“光环”影响下的状态；

aurastatcalc1-6=“光环”影响下的状态计算参数；

auraevent1-3=“光环”影响下可能发生的事件，同events.txt文件关联；

auraeventfunc1-3=当时间发生时调用的功能参数；

auratgtevent=未使用参数；

auratgteventfunc=未使用参数；

passivestate=技能的名称（来自states.txt）；

passiveitype=技能的类型（来自weapons.txt）；

passivestat1-5=被动攻击的状态（主要用于NEC的召唤系列技能）；

passivecalc1-5=如何计算每一种被动状态（同样主要用于NEC）；

passiveevent=无用参数；

passiveeventfunc=无用参数；

summon=召唤的名称（critter/spell/trap）；

pettype=所召唤怪物的类型（同pettype.txt文件关联）；

petmax=一次召唤所允许的最大数量；

summode=所召唤怪物的类型（同monmode.txt文件关联）；

sumskill1-5=所召唤怪物拥有的技能；

sumsk1-5calc=所召唤怪物拥有的技能级别；sumumod=召唤参数（目前只针对“刺客”的技能）；

sumoverlay=所召唤怪物的图像；

stsuccessonly=召唤成功后的声音；

stsound=开始音；

stsoundclass=开始音的音频；

stsounddelay=开始音的祯数；

weaponsnd=角色在使用技能时，武器的伴音；

dosound,a,b=技能使用完毕后，所发出的声音（由怪物的类型决定）；

tgtoverlay=但角色遭受某项技能打击时所显示的图像；

tgtsound=技能在针对敌人时所发出的声音；

prgoverlay=技能在施放过程中所采用的图像；

prgsound=技能在施放过程中所采用的声音；

castoverlay=技能在使用时角色所发生的变化图像；

cltoverlaya,b=技能发出时用户端所显示的图像（通常同战网端进行校对）；

cltstfunc=客户端的功能段；

cltdofunc=客户端直接调用参数的功能段；

cltprgfunc1-3=客户端的程序进程段；

cltmissile -d=客户端调用Missile.txt文件进行校对；

cltcalc1-3=由客户端对技能的影响效果进行校对；

*cltcalc1-3 desc=对于技能计算的描述（没有实际的作用）；

warp=当前技能是否能够转换角色的位置（比如说：SOR的Teleport）；

immediate=“光环”是否立刻发生作用，（1表示立刻起作用，0表示否）；

enhanceable=技能能否被提升，1表示能，0表示不能；

attackrank=无用参数；

noammo=技能是否携带有“装备”，比如说：1代表无魔法属性的箭；

range=物理攻击的范围类型，h2h=赤手攻击，rng=攻击的范围，both=以上两种均具备，none=未使用；

weapsel=当前技能是否有特定武器装备作为限制；

itypea1-3=右手使用当前技能时所必需的武器类型；

etypea1-2=左右手交换攻击的参数；

itypeb1-3=左手使用当前技能时所必需的武器类型；

etypeb1-2=未使用参数；

durability=使用此类技能是否检验角色的“耐力值”是否满足要求，1代表检验； 

TgtPlaceCheck=角色复活时对于技能位置的影响；

ItemEffect=此种技能能否在特定的物品上出现（比如说+2 War Cry的SC）；

ItemCltEffect=nova、frost nova、chain lightning专用的伤害计算参数；

ItemTgtDo=技能能够使所针对的物品做某些事情（E文版的注释说只针对SOR的Teleport，不过我觉得对于NEC的铁石魔也应该有效）；

ItemTarget=限制技能所针对的特定物品或者怪物；

ItemCheckStart=无用参数，建议不要修改；

ItemCltCheckStart=无用参数，建议不要修改；

ItemCastSound=当此项技能来源于一个特定物品的附加属性时，所采用的声音；

ItemCastOverlay=当此项技能来源于一个特定物品的附加属性时，角色图像所发生的变化；s

kpoints=未使用参数；

reqlevel=使用当前技能所需要的角色等级；

maxlvl=当前技能所允许的最大等级；

reqstr=使用当前技能所需要的“强壮”属性；

reqdex=使用当前技能所需要的“敏捷”属性；

reqint=使用当前技能所需要的“魔法”属性；

reqvit=使用当前技能所需要的“生命”属性；

reqskill1-3=使用此技能前必须学会的技能；

restrict=Druid专用参数；

State1-3=使用此项技能所需要的其它因素；

delay=每次使用技能的拖延时间；

leftskill=能否在左面的技能按钮上使用，1代表允许使用；

repeat=在使用此项技能时，如果按钮（或者鼠标）被持续按下，是否不间断的施放技能，1代表允许；

checkfunc=确定物品是否具有合法属性；

nocostinstate=德鲁依变狼、变熊专用参数（1表示无价格）；

usemanaondo=如果一种技能被持续的使用，是否对其所消耗魔法的点数进行缩减；

StartMana=持续性技能专用，在开始时所耗费的魔法数值；

minmana=当前技能所消耗的最小魔法数值；

manashift=魔法除数，用来计算消耗魔法的数量；

mana=当前技能所消耗的魔法数值；

lvlmana=每提升一级技能所需要的魔法数值的增加量；

interrupt=技能在施放过程中能否被打断（1表示可以）；

InTown=技能能否在城镇中使用（1表示可以）；

aura=当前技能是否为“光环”技能（1表示是）；

periodic=技能施放后是否持续的进行攻击，1代表是，比如说：SOR的thunderstorm，ASS的blade shield；

perdelay=技能在转换中两种技能的转换时间差；

finishing=“刺客”技能专用参数；

passive=当前技能是否为被动技能（1表示是被动技能）；

progressive=技能能否被提升（1表示能）；

general=是否每个角色都能够使用当前技能（1表示能）；

scroll=此项技能是否只能由卷轴激发（只用于鉴定和回城）；

calc1-4=技能计算参数；

*calc1-4 desc=对于技能计算参数的注释；

Param1-8=技能参数设置；

*Param1-8 Description=对于技能参数设置的注释；

InGame=技能在游戏中是否起效（1代表起效）；

ToHit=技能为1级时的物理攻击奖赏；

LevToHit=技能额外属性对攻击的奖赏；

ToHitCalc=打击率计算参数，说明：就我看来，好像只对Valkyrie、 bash和stun等技能有效；

ResultFlags=技能参数；

HitFlags=技能参数；

HitClass=技能参数；

Kick=当前技能是否采用“踢”这个动作作为攻击方式；

HitShift=攻击计算除数；

SrcDam=技能伤害参数；

MinDam=当前技能在1级时的最小伤害值；

MinLevDam1-5=对于最小伤害的补充参数；

MaxDam=当前技能在1级时的最大伤害值；

MaxLevDam1-5=对于最大伤害的补充参数；

DmgSymPerCalc=对于“光环”系列的伤害补充参数；

EType=技能的类型，如：attack、fire、cold、ltng、pois、mag；

EMin=所定义的技能类型1级时的最小伤害值；

EMinLev1-5=对于所定义的技能类型最小伤害的补充参数；

EMax=所定义的技能类型1级时的最大伤害值；

EMaxLev1-5=对于所定义的技能类型最大伤害的补充参数；

EDmgSymPerCalc=对于所定义的技能类型最大伤害的补充参数；

ELen=冷冻或者毒素的持续时间（针对所定义的技能类型）；

ELevLen1-3=所定义的技能类型延续时间的技能参数；

ELenSymPerCalc=对于所定义的技能类型伤害值的补充参数；

aitype=如果角色持有武器，那么这种武器在攻击中所发挥的作用；

aibonus=如果角色持有武器，那么这种武器在攻击中所发挥作用的补充值；

cost mult=如果技能在某一特定的武器装备上，此物品的价格；

cost add=如果技能在某一特定的武器装备上，此物品提升价格参数。


*/

/*
文件名解析：
Skill(s)：技能。
此文件描述了游戏中所有技能的部分信息，每一行代表一个技能。


回复

    2楼
    2012-01-05 16:37

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2012-01-05 16:37

    举报 |

    zqtjingzi
    小吧主
    12

Skill：技能的名字索引。

Id：技能的数字索引。

CharClass：技能所属的角色职业。此列决定了“+n 某职业技能”属性对此技能是否有效，以及技能是否出现在某职业的技能列表中。
补充说明：每个职业拥有的技能总数必须相等。

SkillDesc：技能描述的索引，指向SkillDesc.txt。

SrvStFunc：服务器端的技能起始函数。当你点击右键（或左键）时触发此函数。

SrvDoFunc：服务器端的技能执行函数。在起始函数执行完毕后开始执行。当你按住鼠标不放时会重复调用此函数，对于某些特殊技能（如光环类技能）会周期性地自行调用此函数。


回复

    4楼
    2012-01-05 16:38

    举报 |

    zqtjingzi
    小吧主
    12

PrgStack：布尔值。只针对刺客的聚气技能。决定此聚气是否能与其它聚气共同存在。即使用此技能后，是否会取代原有的聚气效果。若此列值为1，则表示可共同存在。

SrvPrgFunc1-3：当前聚气数为1-3时，使用此技能所调用的函数。只针对刺客的聚气技能。

PrgCalc1-3：当前聚气数为1-3时，使用此技能时的参数。只针对刺客的聚气技能。

PrgDam：跟聚气技能相关的一个属性，具体作用不清。只针对刺客的聚气技能。


回复

    5楼
    2012-01-05 16:38

    举报 |

    zqtjingzi
    小吧主
    12

SrvMissile：服务器端的初始投射物。

DecQuant：此技能是否会减少消耗品的数量（如箭矢、标枪、投掷药剂等）。

Lob：布尔值。是否为落地类技能。

srvmissilea-c：服务器端的辅助投射物a-c。

srvoverlay：服务器端控制的显示效果。


回复

    6楼
    2012-01-05 16:38

    举报 |

    zqtjingzi
    小吧主
    12

aurafilter：灵气效果过滤器。决定当前灵气对些单位有效。

aurastate：当前灵气对施放者产生的状态效果。与States.txt关联。

auratargetstate：当前灵气对灵气影响者产生的状态效果。与States.txt关联。

auralencalc：当前灵气效果持续时间的计算公式。

aurarangecalc：当前灵气影响范围的计算公式。

aurastat1-6：灵气效果1-6。与ItemStatCost.txt关联。

aurastatcalc1-6：灵气效果1-6的计算公式。

auraevent1-3：灵气效果触发事件1-3。与Events.txt关联。

auraeventfunc1-3：事件1-3触发灵气效果后的调用函数。

auratgtevent：无用参数。

auratgteventfunc：无用参数。


回复

    7楼
    2012-01-05 16:38

    举报 |

    zqtjingzi
    小吧主
    12

passivestate：当前技能的被动状态。即学习后自动生效的状态。

passiveitype：此被动状态对应的武器类型。与ItemTypes.txt关联。只针对野蛮人的武器掌握技能。

passivestat1-5：当前技能的被动属性1-5。与ItemStatCost.txt关联。

passivecalc1-5：被动属性1-5的计算公式。

passivevent：无用参数。

passiveeventfunc：无用参数。


回复

    8楼
    2012-01-05 16:39

    举报 |

    zqtjingzi
    小吧主
    12

summon：召唤物。与Monstats.txt关联。

pettype：召唤物类型。与PetTyeps.txt关联。

petmax：最大可召唤数量。如此列为空表示没有限制，如骨墙。

summode：召唤物的出生动作。

sumskill1-5：召唤物所掌握的技能。与Skills.txt关联。
补充说明：掌握的技能不一定会使用。召唤物使用什么技能由AI决定。

sumsk1-5calc：召唤物所掌握技能等级的计算公式。

sumumod：召唤物的金怪奖励属性。如特别快速等。与MonUMod.txt关联。
补充说明：这是一个非常有意思的参数。通过修改此列可以让死灵法师的骷髅具有类似金怪的随机灵气，效果非常华丽。



回复

    9楼
    2012-01-05 16:39

    举报 |

    zqtjingzi
    小吧主
    12

sumoverlay：召唤物的外表。


回复

    10楼
    2012-01-05 16:39

    举报 |

    zqtjingzi
    小吧主
    12

stsuccessonly：布尔值。当技能被打断后是否继续此技能的声音或图像效果。

stsound：使用此技能时的声音。与Sounds.txt关联。

stsoundclass：此技能所属职业使用此技能时的声音。为避免如法师使用吼叫类技能时发出野蛮人的声音这样的效果。

stsounddelay：声音是否有延迟。

weaponsnd：布尔值。使用此技能时是否发出武器相关的技能。

dosound：技能执行时的声音。如热诚每次打击都有声音。

dosound a/b：技能执行时的辅助声音a/b。

tgtoverlay：此技能在技能目标上的动画效果。

tgtsound：此技能在技能目标上的声音效果。

prgoverlay：聚气动画效果。只针对刺客的聚气技能。

prgsound：聚气声音效果。只针对刺客的聚气技能。

castoverlay：施法动画效果。

cltoverlaya/b：辅助动画效果a/b。


回复

    11楼
    2012-01-05 16:40

    举报 |

    zqtjingzi
    小吧主
    12

cltstfunc：客户端的技能起始函数。

cltdofunc：客户端的技能执行函数。

cltprgfunc1-3：当前聚气数为1-3时，使用此技能在客户端所调用的函数。只针对刺客的聚气技能。

cltmissile：客户端的初始投射物。

cltmissilea-d：客户端的辅助投射物a-d。

cltcalc1-3：客户端的技能计算公式。


回复

    12楼
    2012-01-05 16:40

    举报 |

    zqtjingzi
    小吧主
    12

warp：布尔值。是否有位置改变。

immediate：布尔值。灵气是否立刻产生效果。只针对灵气类技能。

enhanceable：布尔值。此技能是否可被加强。

attackrank：此技能的攻击等级。决定了怪物受到此技能效果后的反应。

noammo：布尔值，使用此技能是否需要弹药。
补充说明：关于noammo和decquant的区别。noammo决定当你没有弹药时能否使用此技能。而decquant决定使用此技能后是否减少弹药数量。

range：此技能的攻击范围。

weapsel：此技能使用的武器。分为左手、单手、双手、非武器。

itype1-3：使用此技能需要的装备类型1-3。与ItemTypes.txt关联。

etype1-2：不能使用此技能的装备类型。

itypeb1-3：使用此技能需要的副手装备类型。

etypeb1-2：不能使用此技能的副手装备类型。

anim：使用此技能对应的动作类型。与PlrMode.txt关联。

seqtrans：无用参数。

monanim：影子使用此技能对应的动作类型。

seqnum：连续技的动作类型。

seqinput：连续技的时间间隔。

durability：含义未知。

UseAttackRate：布尔值。此技能是否用到攻击准确率。

LineOfSight：是否限制在视野范围内释放。如是否能隔墙释放。

TargetableOnly：含义未知。

SearchEnemyXY：含义未知。
SearchEnemyNear：是否寻找附近的目标。

SearchOpenXY：是否寻找空闲地带。

SelectProc：目标尸体选择参数。

TargetCorpse：是否以尸体为目标。

TargetPet：是否能以召唤物或佣兵为目标。

TargetAlly：是否能以其它玩家为目标。

TargetItem：是否能以物品为目标。

TgtPlaceCheck：是否检查目标位置。

AttackNoMana：没魔法时是否转为普通攻击。

ItemEffect：服务器端当此技能被物品触发时的执行函数。

ItemCltEffect：客户端当此技能被物品触发时的执行函数。

ItemTarget：特殊的目标选择方式。

ItemCheckStart：含义未知。

ItemCltCheckStart：含义未知。

ItemCastSound：当此技能由物品触发时的声音。

ItemCastOverlay：当此技能由物品触发时的动画。


回复

    13楼
    2012-01-05 16:40

    举报 |

    zqtjingzi
    小吧主
    12

skpoints：技能升一级所需要的技能点数。

reqlevel：学习此技能所需要的等级。

maxlvl：此技能可通过技能点达到的最大等级。

reqstr：学习此技能的力量要求。

reqdex：学习此技能的敏捷要求。

reqint：学习此技能的精力要求。

reqvit：学习此技能的体力要求。

reqskill1-3：学习此技能的前置技能1-3。

restrict：使用此技能的状态限制。0=人；1=人或变形；2=固定状态。

state1-3：使用此技能的固定状态限制。与States.txt关联。


回复

    14楼
    2012-01-05 16:41

    举报 |

    zqtjingzi
    小吧主
    12

delay：技能冷却时间，以帧为单位。

leftskill：是否能用左手使用。
补充说明：灵气类技能即使被放在左手也没有效果。

repeat：是否为重复类技能，如地狱火。

checkfunc：状态检查函数。

nocostinstate：变形是否不消耗魔法。即从狼变回人不耗费魔法值。

usemanaondo：持续使用过程中是否不消耗魔法。如地狱火在持续使用过程中会消耗魔法，此列为0。

startmana：使用此魔法的最少魔法要求。

minmana：使用此技能的最小魔法消耗。

manashift：放缩因子。实际放缩比例为shift = 2^(manashift-8)。

mana：初始魔法消耗。

lvlmana：每升一级增加的魔法消耗。
补充说明：最终魔法消耗 = max{ minmana, (mana+lvlmana*(sLvl-1)) * 2^(manashift-8) }

interrupt：是否会被打断。客户端参数。

InTown：是否能在城内使用。

aura：是否为灵气类技能。

periodic：是否为周期性循环技能。

perdelay：灵气类技能以及周期性循环技能的间隔。比如可将雷云风暴的间隔改得很小，会变得很爽。

finishing：是否为结束技。针对刺客聚气技。

passive：是否是被动技能，即是否出现在左、右手的技能列表中。

progressive：是事是聚气技能。

general：是否是通用技能。没有明显作用，更像是注释。

scroll：是否是卷轴类技能。没有明显作用，更像是注释。

calc1-4：技能相关数值的计算公式。由技能函数调用。

param1-8：技能相关参数。

InGame：是否能在游戏中使用。很多余的一个参数，但确实有作用。


回复

    15楼
    2012-01-05 16:41

    举报 |

    zqtjingzi
    小吧主
    12

ToHit：此技能增加的攻击准确率%。

LevToHit：技能等级每提高一级增加的攻击准确率%。

ToHitCalc：此技能增加的攻击准确率公式。当此列不为空时前两列失效。

ResultFlags：含义未知。

HitFlags：含义未知。

HitClass：击打类别。

Kick：是否是踢击。只针对刺客的踢击技能。

HitShift：伤害放缩因子。实际放缩比例shift = 2^(HitShift - 8)。

SrcDamage：普通攻击伤害附加比例。缩减因子为128。

MinDam/MaxDam：技能初始的物理伤害最小值和最大值。

Min/MaxLevDam1-5：技能物理伤害最小值和最大值随技能等级的增加情况。1=2-8；2=9-16；3=17-22；4=23-28；5=29+。

DmgSymPerCalc：技能物理伤害的相关技能加成。

EType：元素伤害类别。与ElemTypes.txt关联。

EMin/Max：技能初始的元素伤害最小值和最大值。

EMin/MaxLev1-5：技能元素伤害最小值和最大值随技能等级的增加情况。1=2-8；2=9-16；3=17-22；4=23-28；5=29+。

EDmgSymPerCalc：技能元素伤害的相关技能加成。

ELen：技能元素伤害的持续时间。

ELevLen1-5：技能元素伤害的持续时间随技能等级增加情况。

ELenSymPerCalc：技能元素伤害的持续时间的相关技能加成。


回复

    16楼
    2012-01-05 16:42

    举报 |

    zqtjingzi
    小吧主
    12

aitype：与AI使用此技能相关。

aibonus：AI使用此技能的机率奖励。

CostMult：此技能作为物品属性对物品价格的提升比例。

CostAdd：此技能作为物品属性对物品价格的提升数值。


回复

    17楼
    2012-01-05 16:42

    举报 |

    firegunkho
    萨卡兰姆
    8

有些MOD是没TXT修改的 修改的BIN文件 怎么改BIN文件 ？


回复

    18楼
    2012-01-05 16:42

    举报 |

    zqtjingzi
    小吧主
    12

关于服务器端和客户端的补充说明：具体如何工作的就不多说了，因为不重要。只要明确跟伤害效果有关的都在服务器端，而客户端基本上只负责动画效果显示就够了。



回复

    19楼
    2012-01-05 16:42

    举报 |

    zqtjingzi
    小吧主
    12

特殊说明：部分资料来源于Nepharius的“SKILLS.TXT FILE GUIDE”

*/

typedef struct
{
    unsigned int vId;

#if 1
    unsigned int vBitCombined;
    unsigned int vBitCombined2;
#else
    unsigned int vinterrupt : 1;
    unsigned int vleftskill : 1;
    unsigned int vItemTgtDo : 1;
    unsigned int vAttackNoMana : 1;

    unsigned int vTargetItem : 1;
    unsigned int vTargetAlly : 1;
    unsigned int vTargetPet : 1;
    unsigned int vTargetCorpse : 1;

    unsigned int vSearchOpenXY : 1;
    unsigned int vSearchEnemyNear : 1;
    unsigned int vSearchEnemyXY : 1;
    unsigned int vTargetableOnly : 1;

    unsigned int vUseAttackRate : 1;
    unsigned int vdurability : 1;
    unsigned int venhanceable : 1;
    unsigned int vnoammo : 1;

    unsigned int vimmediate : 1;
    unsigned int vweaponsnd : 1;
    unsigned int vstsounddelay : 1;
    unsigned int vstsuccessonly : 1;

    unsigned int vrepeat : 1;
    unsigned int vInGame : 1;
    unsigned int vKick : 1;
    unsigned int vInTown : 1;

    unsigned int vprgstack : 1;
    unsigned int vperiodic : 1;
    unsigned int vaura : 1;
    unsigned int vpassive : 1;

    unsigned int vfinishing : 1;
    unsigned int vprogressive : 1;
    unsigned int vlob : 1;
    unsigned int vdecquant : 1;

    unsigned int iPadding2 : 25;
    unsigned int vwarp : 1;
    unsigned int vusemanaondo : 1;
    unsigned int vscroll : 1;

    unsigned int vgeneral : 1;
    unsigned int vItemCltCheckStart : 1;
    unsigned int vItemCheckStart : 1;
    unsigned int vTgtPlaceCheck : 1;
#endif

    unsigned char vcharclass;   //playerclass
    char iPadding3[3];

    unsigned char vanim;    //plrmode
    unsigned char vmonanim;    //monmode
    unsigned char vseqtrans;    //plrmode
    unsigned char vseqnum;

    unsigned char vrange;
    unsigned char vSelectProc;
    unsigned short vseqinput;

    unsigned short vitypea1;    //ItemTypes
    unsigned short vitypea2;    //ItemTypes

    unsigned short vitypea3;    //ItemTypes
    unsigned short vitypeb1;    //ItemTypes

    unsigned short vitypeb2;    //ItemTypes
    unsigned short vitypeb3;    //ItemTypes

    unsigned short vetypea1;    //ItemTypes
    unsigned short vetypea2;    //ItemTypes

    unsigned short vetypeb1;    //ItemTypes
    unsigned short vetypeb2;    //ItemTypes

    unsigned short vsrvstfunc;
    unsigned short vsrvdofunc;

    unsigned short vsrvprgfunc1;
    unsigned short vsrvprgfunc2;

    unsigned short vsrvprgfunc3;
    unsigned short iPadding13;

    unsigned int vprgcalc1;     //skillscode
    unsigned int vprgcalc2;
    unsigned int vprgcalc3;

    unsigned short vprgdam;
    unsigned short vsrvmissile;     //missile

    unsigned short vsrvmissilea;     //missile
    unsigned short vsrvmissileb;    //missile

    unsigned short vsrvmissilec;    //missile
    unsigned short vsrvoverlay;     //overlay

    unsigned int vaurafilter;

    unsigned short vaurastat1;  //ItemStatCost
    unsigned short vaurastat2;  //ItemStatCost
    unsigned short vaurastat3;  //ItemStatCost
    unsigned short vaurastat4;  //ItemStatCost
    unsigned short vaurastat5;  //ItemStatCost
    unsigned short vaurastat6;  //ItemStatCost

    unsigned int vauralencalc;      //skillscode
    unsigned int vaurarangecalc;
    unsigned int vaurastatcalc1;
    unsigned int vaurastatcalc2;
    unsigned int vaurastatcalc3;
    unsigned int vaurastatcalc4;
    unsigned int vaurastatcalc5;
    unsigned int vaurastatcalc6;

    unsigned short vaurastate;  //state
    unsigned short vauratargetstate;    //state

    unsigned short vauraevent1; //event
    unsigned short vauraevent2; //event

    unsigned short vauraevent3; //event
    unsigned short vauraeventfunc1;

    unsigned short vauraeventfunc2;
    unsigned short vauraeventfunc3;

    unsigned short vauratgtevent;   //event
    unsigned short vauratgteventfunc;

    unsigned short vpassivestate;   //state
    unsigned short vpassiveitype;   //itemtypes

    unsigned short vpassivestat1;   //ItemStatCost
    unsigned short vpassivestat2;   //ItemStatCost

    unsigned short vpassivestat3;   //ItemStatCost
    unsigned short vpassivestat4;   //ItemStatCost

    unsigned short vpassivestat5;   //ItemStatCost
    unsigned short iPadding40;

    unsigned int vpassivecalc1; //skillscode
    unsigned int vpassivecalc2;
    unsigned int vpassivecalc3;
    unsigned int vpassivecalc4;
    unsigned int vpassivecalc5;

    unsigned short vpassiveevent;   //events
    unsigned short vpassiveeventfunc;

    unsigned short vsummon; //MonStats
    unsigned char vpettype; //PetType
    unsigned char vsummode; //MonMode

    unsigned int vpetmax;   //skillscode

    unsigned short vsumskill1;  //skills
    unsigned short vsumskill2;  //skills

    unsigned short vsumskill3;  //skills
    unsigned short vsumskill4;  //skills

    unsigned short vsumskill5;  //skills
    unsigned short iPadding51;

    unsigned int vsumsk1calc;   //skillscode
    unsigned int vsumsk2calc;
    unsigned int vsumsk3calc;
    unsigned int vsumsk4calc;
    unsigned int vsumsk5calc;

    unsigned short vsumumod;
    unsigned short vsumoverlay; //overlay

    unsigned short vcltmissile; //missiles
    unsigned short vcltmissilea;    //missiles
    unsigned short vcltmissileb;    //missiles
    unsigned short vcltmissilec;    //missiles

    unsigned short vcltmissiled;    //missiles
    unsigned short vcltstfunc;

    unsigned short vcltdofunc;
    unsigned short vcltprgfunc1;

    unsigned short vcltprgfunc2;
    unsigned short vcltprgfunc3;

    unsigned short vstsound;    //sounds
    unsigned short vstsoundclass;   //sounds

    unsigned short vdosound;    //sounds
    unsigned short vdosoundmyspa; //sounds

    unsigned short vdosoundmyspb; //sounds
    unsigned short vcastoverlay;    //overlay

    unsigned short vtgtoverlay; //overlay
    unsigned short vtgtsound;    //sounds

    unsigned short vprgoverlay; //overlay
    unsigned short vprgsound;   //sounds

    unsigned short vcltoverlaya;    //overlay
    unsigned short vcltoverlayb;    //overlay

    unsigned int vcltcalc1; //skillscode
    unsigned int vcltcalc2;
    unsigned int vcltcalc3;

    unsigned char vItemTarget;
    unsigned char iPadding72;
    unsigned short vItemCastSound;  //sounds

    unsigned short vItemCastOverlay;    //overlay
    unsigned short iPadding73;

    unsigned int vperdelay; //skillscode

    unsigned short vmaxlvl;
    unsigned short vResultFlags;

    unsigned int vHitFlags;
    unsigned int vHitClass;

    unsigned int vcalc1;    //skillscode
    unsigned int vcalc2;
    unsigned int vcalc3;
    unsigned int vcalc4;

    int vParam1;
    int vParam2;
    int vParam3;
    int vParam4;
    int vParam5;
    int vParam6;
    int vParam7;
    int vParam8;

    unsigned short vweapsel;
    unsigned short vItemEffect;

    unsigned short vItemCltEffect;
    unsigned short iPadding91;

    unsigned int vskpoints; //skillscode

    unsigned short vreqlevel;
    unsigned short vreqstr;

    unsigned short vreqdex;
    unsigned short vreqint;

    unsigned short vreqvit;
    unsigned short vreqskill1;  //skills

    unsigned short vreqskill2;  //skills
    unsigned short vreqskill3;  //skills

    unsigned short vstartmana;
    unsigned short vminmana;

    unsigned short vmanashift;
    unsigned short vmana;

    short vlvlmana;
    unsigned char vattackrank;
    unsigned char vLineOfSight;

    unsigned int vdelay;    //skillscode

    unsigned short vskilldesc;  //skilldesc
    unsigned short iPadding101;

    unsigned int vToHit;
    unsigned int vLevToHit;

    unsigned int vToHitCalc;    //skillscode

    unsigned char vHitShift;
    unsigned char vSrcDam;
    unsigned short iPadding105;

    unsigned int vMinDam;
    unsigned int vMaxDam;
    unsigned int vMinLevDam1;
    unsigned int vMinLevDam2;

    unsigned int vMinLevDam3;
    unsigned int vMinLevDam4;
    unsigned int vMinLevDam5;
    unsigned int vMaxLevDam1;
    unsigned int vMaxLevDam2;
    unsigned int vMaxLevDam3;
    unsigned int vMaxLevDam4;
    unsigned int vMaxLevDam5;

    unsigned int vDmgSymPerCalc;    //skillscode

    unsigned short vEType;  //elemtypes
    unsigned short iPadding119;

    unsigned int vEMin;
    unsigned int vEMax;
    unsigned int vEMinLev1;
    unsigned int vEMinLev2;
    unsigned int vEMinLev3;
    unsigned int vEMinLev4;
    unsigned int vEMinLev5;
    unsigned int vEMaxLev1;
    unsigned int vEMaxLev2;
    unsigned int vEMaxLev3;
    unsigned int vEMaxLev4;
    unsigned int vEMaxLev5;

    unsigned int vEDmgSymPerCalc;   //skillscode
    unsigned int vELen;
    unsigned int vELevLen1;
    unsigned int vELevLen2;
    unsigned int vELevLen3;
    unsigned int vELenSymPerCalc;   //skillscode

    unsigned short vrestrict;
    unsigned short vState1;     //states

    unsigned short vState2;     //states
    unsigned short vState3;     //states

    unsigned short vaitype;
    short vaibonus;
    unsigned int vcostmyspmult;
    unsigned int vcostmyspadd;
} ST_LINE_INFO;

typedef struct
{
    char vskill[32];
} ST_SKILLS;

static char *m_apcNotUsed[] = 
{
    "checkfunc",
    "nocostinstate",
    "*cltcalc1 desc",
    "*cltcalc2 desc",
    "*cltcalc3 desc",
    "*calc1 desc",
    "*calc2 desc",
    "*calc3 desc",
    "*calc4 desc",
    "*Param1 Description",
    "*Param2 Description",
    "*Param3 Description",
    "*Param4 Description",
    "*Param5 Description",
    "*Param6 Description",
    "*Param7 Description",
    "*Param8 Description",
    NULL,
};

static char *m_apcInternalProcess[] = 
{
    "skill",
    NULL,
};

static unsigned int m_iSkillsCount = 0;
static ST_SKILLS *m_astSkills = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astSkills, ST_SKILLS);

static int Skills_FieldProc_Pre(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "skill") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
        }

        strncpy(m_astSkills[m_iSkillsCount].vskill, acOutput, sizeof(m_astSkills[m_iSkillsCount].vskill));
        String_Trim(m_astSkills[m_iSkillsCount].vskill);
        m_iSkillsCount++;
        return 1;
    }

    return 0;
}

static int Skills_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "skill") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
        }
        return 1;
    }

    return 0;
}

static int Skills_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "charclass") )
    {
        pcResult = PlayerClass_GetClass(pstLineInfo->vcharclass);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
        }
    else if ( !strcmp(acKey, "skilldesc") )
    {
        pcResult = SkillDesc_GetDesc(pstLineInfo->vskilldesc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "anim") )
    {
        pcResult = PlrMode_GetCode(pstLineInfo->vanim);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "monanim") )
    {
        pcResult = MonMode_GetCode(pstLineInfo->vmonanim);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "seqtrans") )
    {
        pcResult = PlrMode_GetCode(pstLineInfo->vseqtrans);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "monanim") )
    {
        pcResult = MonMode_GetCode(pstLineInfo->vmonanim);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "itypea1") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitypea1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "itypea2") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitypea2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "itypea3") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitypea3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "etypea1") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vetypea1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "etypea2") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vetypea2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "itypeb1") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitypeb1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "itypeb2") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitypeb2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "itypeb3") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitypeb3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "etypeb1") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vetypeb1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "etypeb2") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vetypeb2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "srvmissile") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vsrvmissile);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "srvmissilea") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vsrvmissilea);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "srvmissileb") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vsrvmissileb);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "srvmissilec") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vsrvmissilec);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "srvoverlay") )
    {
        pcResult = Overlay_GetOverlay(pstLineInfo->vsrvoverlay);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastat1") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vaurastat1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastat2") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vaurastat2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastat3") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vaurastat3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastat4") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vaurastat4);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastat5") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vaurastat5);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastat6") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vaurastat6);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastate") )
    {
        pcResult = States_GetStateName(pstLineInfo->vaurastate);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "auratargetstate") )
    {
        pcResult = States_GetStateName(pstLineInfo->vauratargetstate);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "auraevent1") )
    {
        pcResult = Events_GetEventName(pstLineInfo->vauraevent1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "auraevent2") )
    {
        pcResult = Events_GetEventName(pstLineInfo->vauraevent2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "auraevent3") )
    {
        pcResult = Events_GetEventName(pstLineInfo->vauraevent3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "auratgtevent") )
    {
        pcResult = Events_GetEventName(pstLineInfo->vauratgtevent);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passivestate") )
    {
        pcResult = States_GetStateName(pstLineInfo->vpassivestate);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passiveitype") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vpassiveitype);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passivestat1") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vpassivestat1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passivestat2") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vpassivestat2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passivestat3") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vpassivestat3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passivestat4") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vpassivestat4);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passivestat5") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vpassivestat5);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passiveevent") )
    {
        pcResult = Events_GetEventName(pstLineInfo->vpassiveevent);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "summon") )
    {
        pcResult = MonStats_GetStatsName(pstLineInfo->vsummon);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "pettype") )
    {
        pcResult = Pettype_GetPetType(pstLineInfo->vpettype);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "summode") )
    {
        pcResult = MonMode_GetCode(pstLineInfo->vsummode);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "sumskill1") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vsumskill1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "sumskill2") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vsumskill2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "sumskill3") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vsumskill3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "sumskill4") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vsumskill4);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "sumskill5") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vsumskill5);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "sumoverlay") )
    {
        pcResult = Overlay_GetOverlay(pstLineInfo->vsumoverlay);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "cltmissile") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vcltmissile);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "cltmissilea") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vcltmissilea);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "cltmissileb") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vcltmissileb);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "cltmissilec") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vcltmissilec);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "cltmissiled") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vcltmissiled);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "stsound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vstsound);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "stsoundclass") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vstsoundclass);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "dosound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vdosound);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "dosound a") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vdosoundmyspa);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "dosound b") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vdosoundmyspb);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "castoverlay") )
    {
        pcResult = Overlay_GetOverlay(pstLineInfo->vcastoverlay);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "tgtoverlay") )
    {
        pcResult = Overlay_GetOverlay(pstLineInfo->vtgtoverlay);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "tgtsound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vtgtsound);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "prgoverlay") )
    {
        pcResult = Overlay_GetOverlay(pstLineInfo->vprgoverlay);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "prgsound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vprgsound);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "cltoverlaya") )
    {
        pcResult = Overlay_GetOverlay(pstLineInfo->vcltoverlaya);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "cltoverlayb") )
    {
        pcResult = Overlay_GetOverlay(pstLineInfo->vcltoverlayb);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "ItemCastSound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vItemCastSound);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "ItemCastOverlay") )
    {
        pcResult = Overlay_GetOverlay(pstLineInfo->vItemCastOverlay);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "reqskill1") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vreqskill1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "reqskill2") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vreqskill2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "reqskill3") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vreqskill3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "skilldesc") )
    {
        pcResult = SkillDesc_GetDesc(pstLineInfo->vskilldesc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "EType") )
    {
        pcResult = ElemTypes_GetElemStr(pstLineInfo->vEType);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "State1") )
    {
        pcResult = States_GetStateName(pstLineInfo->vState1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "State2") )
    {
        pcResult = States_GetStateName(pstLineInfo->vState2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "State3") )
    {
        pcResult = States_GetStateName(pstLineInfo->vState3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "range") )
    {
        if ( 3 == pstLineInfo->vrange )
        {
            strcpy(acOutput, "both");
        }
        else if ( 1 == pstLineInfo->vrange )
        {
            strcpy(acOutput, "h2h");
        }
        else if ( 2 == pstLineInfo->vrange )
        {
            strcpy(acOutput, "rng");
        }
        else if ( 0 == pstLineInfo->vrange )
        {
            strcpy(acOutput, "none");
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "prgcalc1") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vprgcalc1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "prgcalc2") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vprgcalc2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "prgcalc3") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vprgcalc3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "auralencalc") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vauralencalc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurarangecalc") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vaurarangecalc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastatcalc1") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vaurastatcalc1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastatcalc2") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vaurastatcalc2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastatcalc3") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vaurastatcalc3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastatcalc4") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vaurastatcalc4);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastatcalc5") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vaurastatcalc5);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "aurastatcalc6") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vaurastatcalc6);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passivecalc1") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vpassivecalc1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passivecalc2") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vpassivecalc2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passivecalc3") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vpassivecalc3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passivecalc4") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vpassivecalc4);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "passivecalc5") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vpassivecalc5);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "petmax") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vpetmax);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "sumsk1calc") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vsumsk1calc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "sumsk2calc") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vsumsk2calc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "sumsk3calc") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vsumsk3calc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "sumsk4calc") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vsumsk4calc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "sumsk5calc") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vsumsk5calc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "cltcalc1") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vcltcalc1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "cltcalc2") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vcltcalc2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "cltcalc3") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vcltcalc3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "perdelay") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vperdelay);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "calc1") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vcalc1);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "calc2") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vcalc2);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "calc3") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vcalc3);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "calc4") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vcalc4);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "skpoints") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vskpoints);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "delay") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vdelay);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "ToHitCalc") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vToHitCalc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "DmgSymPerCalc") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vDmgSymPerCalc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "EDmgSymPerCalc") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vEDmgSymPerCalc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "ELenSymPerCalc") )
    {
        pcResult = SkillsCode_GetExpression(pstLineInfo->vELenSymPerCalc);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }

    return result;
}

static int Skills_BitProc(void *pvLineInfo, char *acKey, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp(acKey, "interrupt") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 31)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "leftskill") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 30)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "ItemTgtDo") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 29)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "AttackNoMana") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 28)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "TargetItem") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 27)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "TargetAlly") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 26)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "TargetPet") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 25)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "TargetCorpse") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 24)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "SearchOpenXY") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 23)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "SearchEnemyNear") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 22)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "SearchEnemyXY") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 21)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "TargetableOnly") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 20)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "UseAttackRate") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 19)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "durability") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 18)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "enhanceable") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 17)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "noammo") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 16)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "immediate") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 15)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "weaponsnd") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 14)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "stsounddelay") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 13)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "stsuccessonly") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 12)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "repeat") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 11)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "InGame") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 10)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "Kick") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 9)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "InTown") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 8)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "prgstack") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 7)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "periodic") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 6)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "aura") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 5)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "passive") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "finishing") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "progressive") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "lob") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "decquant") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & 1) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "warp") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 6)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "usemanaondo") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 5)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "scroll") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "general") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "ItemCltCheckStart") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "ItemCheckStart") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "TgtPlaceCheck") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & 1) != 0);
        result = 1;
    }

    return result;
}

static void Skills_InitValueMap(ST_VALUE_MAP *pstValueMap, ST_LINE_INFO *pstLineInfo)
{
    INIT_VALUE_BUFFER;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Id, UINT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, interrupt, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, ItemTgtDo, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, leftskill, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, AttackNoMana, BitCombined, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, TargetItem, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, TargetAlly, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, TargetPet, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, TargetCorpse, BitCombined, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, SearchOpenXY, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, SearchEnemyNear, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, SearchEnemyXY, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, TargetableOnly, BitCombined, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, UseAttackRate, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, durability, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, enhanceable, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, noammo, BitCombined, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, immediate, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, weaponsnd, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, stsounddelay, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, stsuccessonly, BitCombined, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, repeat, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, InGame, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, Kick, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, InTown, BitCombined, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, prgstack, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, periodic, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, aura, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, passive, BitCombined, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, finishing, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, progressive, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, lob, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, decquant, BitCombined, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, warp, BitCombined2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, usemanaondo, BitCombined2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, scroll, BitCombined2, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, general, BitCombined2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, ItemCltCheckStart, BitCombined2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, ItemCheckStart, BitCombined2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, TgtPlaceCheck, BitCombined2, BIT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, charclass, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, anim, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, monanim, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, seqtrans, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, seqnum, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, range, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SelectProc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, seqinput, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itypea1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itypea2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itypea3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etypea1, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etypea2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itypeb1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itypeb2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itypeb3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etypeb1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etypeb2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, srvstfunc, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, srvdofunc, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, srvprgfunc1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, srvprgfunc2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, srvprgfunc3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prgdam, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, srvmissile, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, srvmissilea, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, srvmissileb, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, srvmissilec, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, srvoverlay, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurafilter, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastat1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastat2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastat3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastat4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastat5, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastat6, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastate, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, auratargetstate, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, auraevent1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, auraevent2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, auraevent3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, auraeventfunc1, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, auraeventfunc2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, auraeventfunc3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, auratgtevent, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, auratgteventfunc, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passivestate, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passiveitype, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passivestat1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passivestat2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passivestat3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passivestat4, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passivestat5, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passiveevent, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passiveeventfunc, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, summon, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, pettype, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, summode, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumskill1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumskill2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumskill3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumskill4, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumskill5, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumumod, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumoverlay, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltmissile, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltmissilea, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltmissileb, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltmissilec, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltmissiled, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltstfunc, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltdofunc, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltprgfunc1, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltprgfunc2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltprgfunc3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stsound, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stsoundclass, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dosound, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dosoundmyspa, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dosoundmyspb, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, castoverlay, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, tgtoverlay, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, tgtsound, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prgoverlay, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prgsound, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltoverlaya, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltoverlayb, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ItemTarget, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ItemCastSound, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ItemCastOverlay, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxlvl, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ResultFlags, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitFlags, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitClass, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param4, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param5, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param6, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param7, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param8, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, weapsel, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ItemEffect, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ItemCltEffect, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, reqlevel, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, reqstr, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, reqdex, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, reqint, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, reqvit, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, reqskill1, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, reqskill2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, reqskill3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, startmana, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, minmana, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, manashift, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mana, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lvlmana, SHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, attackrank, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LineOfSight, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, skilldesc, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ToHit, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LevToHit, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitShift, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SrcDam, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinDam, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxDam, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinLevDam1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinLevDam2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinLevDam3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinLevDam4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinLevDam5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxLevDam1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxLevDam2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxLevDam3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxLevDam4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxLevDam5, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EType, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMin, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMax, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMinLev1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMinLev2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMinLev3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMinLev4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMinLev5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMaxLev1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMaxLev2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMaxLev3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMaxLev4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMaxLev5, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ELen, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ELevLen1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ELevLen2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ELevLen3, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, restrict, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, State1, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, State2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, State3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aitype, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aibonus, SHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, costmyspmult, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, costmyspadd, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prgcalc1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prgcalc2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prgcalc3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, auralencalc, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurarangecalc, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastatcalc1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastatcalc2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastatcalc3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastatcalc4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastatcalc5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aurastatcalc6, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passivecalc1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passivecalc2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passivecalc3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passivecalc4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, passivecalc5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, petmax, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumsk1calc, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumsk2calc, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumsk3calc, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumsk4calc, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sumsk5calc, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltcalc1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltcalc2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cltcalc3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, perdelay, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, calc1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, calc2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, calc3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, calc4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, skpoints, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, delay, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ToHitCalc, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DmgSymPerCalc, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EDmgSymPerCalc, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ELenSymPerCalc, UINT);
}

int process_skills(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            Skills_InitValueMap(pstValueMap, pstLineInfo);

            m_stCallback.pfnFieldProc = Skills_FieldProc_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            m_iSkillsCount = 0;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(playerclass, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(skilldesc, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(plrmode, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(monmode, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(itemtypes, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(missiles, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(overlay, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(itemstatcost, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(states, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(events, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(monstats, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(pettype, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(skills, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(sounds, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(elemtypes, acTemplatePath, acBinPath, acTxtPath);

            if ( 0 == SkillsCode_ParseBin(acTemplatePath, acBinPath, acTxtPath) )
            {
                return 0;
            }
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            Skills_InitValueMap(pstValueMap, pstLineInfo);

            m_stCallback.pfnFieldProc = Skills_FieldProc;
            m_stCallback.pfnConvertValue = Skills_ConvertValue;
            m_stCallback.pfnBitProc = Skills_BitProc;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

char *Skills_GetSkillName(unsigned int id)
{
    if ( id >= m_iSkillsCount )
    {
        return NULL;
    }

    return m_astSkills[id].vskill;
}

/*
What you can do is make a summon that has a summon skill when it dies. This is the most simple way but it will only allow you to have 1 summon at a time. Or they will all appear when you kill the 'central' summon.

A more complicated way involves using special invisible monsters that summons on death, make these monsters have a -hpregen if a certain stat = 0. And give all monsters an aura that gives that stat (invisible aura) when all monsters die that stat will 
drop to 0 on the invisible monster, it will die and summon the next wave. It's a bit complicated but if you're crazy enough you can try it.

*/

