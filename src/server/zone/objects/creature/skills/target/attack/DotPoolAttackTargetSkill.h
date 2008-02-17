/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/

#ifndef DOTPOOLATTACKTARGETSKILL_H_
#define DOTPOOLATTACKTARGETSKILL_H_

#include "../AttackTargetSkill.h"

class DotPoolAttackTargetSkill : public AttackTargetSkill {
protected:

	int dotChanceState;
	bool tickStrengthOfHit;
	
	int fireDotType;
	int fireDotStrength;
	
	int bleedingDotType;
	int bleedingDotStrength;
	
	int poisonDotType;
	int poisonDotStrength;
	
	int diseaseDotType;
	int diseaseDotStrength;

public:
	DotPoolAttackTargetSkill(const string& name, const string& anim, ZoneProcessServerImplementation* serv) : AttackTargetSkill(name, anim, serv) {
		
		dotChanceState = 0;
		
		fireDotType = 0;
		fireDotStrength = 0;
		
		bleedingDotType = 0;
		bleedingDotStrength = 0;
		
		poisonDotType = 0;
		poisonDotStrength = 0;
		
		diseaseDotType = 0;
		diseaseDotStrength = 0;
		
		tickStrengthOfHit= false;
		
	}
	
	int doSkill(CreatureObject* creature, CreatureObject* targetCreature, bool doAnimation = true) {
		int damage = calculateDamage(creature, targetCreature);
		
		/*if (doAnimation) {
			if (animCRC == 0 && creature->isPlayer()) {
				Player* player = (Player*) creature;
				string anim = Animations::getRandomAnimation();
				uint32 animationCRC = String::hashCode(anim);
				player->doCombatAnimation(targetCreature, animationCRC, 1);
				creature->sendSystemMessage(anim);
			} else
				creature->doCombatAnimation(targetCreature, animCRC, (damage > 0));
		}*/
		if (damage && targetCreature->hasAttackDelay())
			targetCreature->clearAttackDelay();
		
		doAnimations(creature, targetCreature);
		
		return damage;
	}
	
	int calculateDamage(CreatureObject* creature, CreatureObject* targetCreature) {
		Weapon* weapon = creature->getWeapon();
		float minDamage = 0;
		float maxDamage = 0; 
		float healthDamage = 0;
		float actionDamage = 0;
		float mindDamage = 0;
		int bodyPart = 0;
		int reduction = 0;
		
		if (weapon != NULL) {
			minDamage = weapon->getMinDamage();
			maxDamage = weapon->getMaxDamage();
		} else {
			maxDamage = (float)creature->getSkillMod("unarmed_damage");
			if (maxDamage < 25)
				maxDamage = 25;
			minDamage = maxDamage / 2;
		}
		
		checkMitigation(creature, targetCreature, minDamage, maxDamage);

		float damage = 0;
		int average = (System::random((int)maxDamage - (int)minDamage) + (int)minDamage);
			
		if (getHitChance(creature, targetCreature) > System::random(100)) {
			
			int secondaryDefense = checkSecondaryDefenses(creature, targetCreature);
			
			if (secondaryDefense < 2) {
				if (secondaryDefense == 1)
					damage = damage / 2;
					
				if (healthPoolAttackChance != 0 && System::random(100) < healthPoolAttackChance) {
					healthDamage = -damageRatio * average;
					calculateDamageReduction(creature, targetCreature, healthDamage);
					bodyPart = System::random(5)+1;
					
					damage += healthDamage;
				} else if (actionPoolAttackChance != 0 && System::random(100) < actionPoolAttackChance) {
					actionDamage = -damageRatio * average;
					calculateDamageReduction(creature, targetCreature,  actionDamage);
					bodyPart = System::random(1)+7;

					damage += actionDamage;
				} else if (mindPoolAttackChance != 0 && System::random(100) < mindPoolAttackChance) {
					mindDamage = -damageRatio * average;
					calculateDamageReduction(creature, targetCreature,  mindDamage);
					bodyPart = 9;

					damage += mindDamage;
				}
			} else {
				return 0;
			}
		
			if (damage == 0) {
				doMiss(creature, targetCreature, (int32) damage);
				return 0;
		 	} else 	 	
		 		checkDots(targetCreature, damage);

			if (hasCbtSpamHit()) 
				creature->sendCombatSpam(targetCreature, NULL, -(int32)damage, getCbtSpamHit());
			
			if (bodyPart < 7)
				reduction = applyHealthPoolDamage(creature, targetCreature, (int32) healthDamage, bodyPart);
			else if (bodyPart < 9)
				reduction = applyActionPoolDamage(creature, targetCreature, (int32) actionDamage, bodyPart);
			else if (bodyPart == 9)
				reduction = applyMindPoolDamage(creature, targetCreature, (int32) mindDamage);
			
		} else {
			doMiss(creature, targetCreature, (int32) damage);
			return 0;
		}
		
		return -(int32)damage - reduction;
	}
	
	void checkDots(CreatureObject* targetCreature, float damage) {
		int bleedResist = 0;
		int diseaseResist = 0;
		int fireResist = 0;
		int poisonResist = 0;
		
		if (fireDotType > 0)
			fireResist += targetCreature->getSkillMod("resistance_fire");
		if (bleedingDotType > 0)
			bleedResist += targetCreature->getSkillMod("resistance_bleeding");
		if (poisonDotType > 0)
			poisonResist += targetCreature->getSkillMod("resistance_poison");
		if (diseaseDotType > 0)
			diseaseResist += targetCreature->getSkillMod("resistance_disease");			
	
		if (dotChanceState > 0 && System::random(100) < dotChanceState) {
		
		if (fireDotType > 0 && dotChanceState > 0 && System::random(100) < (dotChanceState-fireResist)) {
				if (tickStrengthOfHit)
					fireDotStrength = -(int)(damage / 5);	
				targetCreature->setOnFireState(fireDotStrength, fireDotType, 60);
		}
		
		if (bleedingDotType > 0 && dotChanceState > 0 && System::random(100) < (dotChanceState-bleedResist)) {
			if (tickStrengthOfHit)
				bleedingDotStrength = -(int)(damage / 5);
			targetCreature->setBleedingState(bleedingDotStrength, bleedingDotType, 60);
		}
		
		if (poisonDotType > 0 && dotChanceState > 0 && System::random(100) < (dotChanceState-poisonResist)) {
			if (tickStrengthOfHit)
			poisonDotStrength = -(int)(damage / 5);
			targetCreature->setPoisonedState(poisonDotStrength, poisonDotType, 60);
		}
		
		if (diseaseDotType > 0 && dotChanceState > 0 && System::random(100) < (dotChanceState-diseaseResist)) {
			if (tickStrengthOfHit)
				diseaseDotStrength = -(int)(damage / 5);
			targetCreature->setDiseasedState(diseaseDotStrength, diseaseDotType, 60);
		}
		
		targetCreature->updateStates();
		}
	}

	virtual bool calculateCost(CreatureObject* creature) {
		if (!creature->isPlayer())
			return true;
		
		Player* player = (Player*)creature;
		Weapon* weapon = creature->getWeapon();
		
		if (weapon != NULL) {
			
			int healthAttackCost = weapon->getHealthAttackCost();
			int actionAttackCost = weapon->getActionAttackCost();
			int mindAttackCost = weapon->getMindAttackCost();
			
			if (!player->changeHAMBars(-healthAttackCost, -actionAttackCost, -mindAttackCost))
				return false;
		}

		return true; 
	}
	
	void setDotChance(int dotchance) {
		dotChanceState = dotchance;
	}
	
	void setFireDotStrength(int str) {
		fireDotStrength = str;
	}
	
	void setFireDotType(int tp) {
		fireDotType = tp;
	}
	
	void setBleedingDotStrength(int str) {
		bleedingDotStrength = str;
	}
	
	void setBleedingDotType(int tp) {
		bleedingDotType = tp;
	}
	
	void setPoisonDotStrength(int str) {
		poisonDotStrength = str;
	}
	
	void setPoisonDotType(int tp) {
		poisonDotType = tp;
	}
	
	void setDiseaseDotStrength(int str) {
		diseaseDotStrength = str;
	}
	
	void setDiseaseDotType(int tp) {
		diseaseDotType = tp;
	}
	
	void setTickStrengthOfHit(bool t) {
		tickStrengthOfHit = t;
	}
	
};

#endif /*DOTPOOLATTACKTARGETSKILL_H_*/
