/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cRocket.h"
#include "cWNDManager.h"
#include <iostream>

void cRocket::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cRocket::update(float deltaTime)
{
	
	spriteRotation = +90.0f;
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spriteTranslation = (glm::vec2(4.0f, 4.0f));
		
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spriteTranslation = -(glm::vec2(4.0f, 4.0f));
	}
	if (m_InputMgr->isKeyDown(VK_UP))
	{
		
	}
	if (m_InputMgr->isKeyDown(VK_DOWN))
	{
		for (int tres = 0; tres < 10; tres++)
		{
			theAsteroids.push_back(new cAsteroid);
			theAsteroids[tres]->setSpritePos(glm::vec2(1024 / (rand() % 5 + 1), 786 / (rand() % 5 + 1)));
			theAsteroids[tres]->setSpriteTranslation(glm::vec2((22.0f, 22.0f)));
			theAsteroids[tres]->setTexture(theGameTextures[rand() % 4]->getTexture());
			theAsteroids[tres]->setTextureDimensions(theGameTextures[rand() % 4]->getTWidth(), theGameTextures[rand() % 4]->getTHeight());
			theAsteroids[tres]->setSpriteCentre();
			theAsteroids[tres]->setAsteroidVelocity(glm::vec2(glm::vec2(20.0f, 20.0f)));
			theAsteroids[tres]->setActive(true);
			theAsteroids[tres]->setMdlRadius();
		}
		
	}
	if (m_InputMgr->isKeyDown(int('A')))
	{
		spriteScaling += 0.2f;
	}
	if (m_InputMgr->isKeyDown(int('S')))
	{
		spriteScaling -= 0.2f;
	}
if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		spriteTranslation = (glm::vec2(0.0f, 0.0f));
		theRocketBullets.push_back(new cBullet);
		int numBullets = theRocketBullets.size() - 1;
		theRocketBullets[numBullets]->setSpritePos(glm::vec2(spritePos2D.x + spriteCentre.x, spritePos2D.y - 50));
		theRocketBullets[numBullets]->setSpriteTranslation(glm::vec2(0.0f, 0.0f));
		theRocketBullets[numBullets]->setTexture(theGameTextures[4]->getTexture());
		theRocketBullets[numBullets]->setTextureDimensions(theGameTextures[4]->getTWidth(), theGameTextures[4]->getTHeight());
		theRocketBullets[numBullets]->setSpriteCentre();
		theRocketBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
		theRocketBullets[numBullets]->setSpriteRotation(getSpriteRotation()-90);
		theRocketBullets[numBullets]->setActive(true);
		theRocketBullets[numBullets]->setMdlRadius();
	}


	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}

	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	rocketVelocity += spriteVelocityAdd;

	spritePos2D += rocketVelocity * deltaTime;

	rocketVelocity *= 0.95;

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cBullet*>::iterator index = theRocketBullets.begin(); index != theRocketBullets.end(); ++index)
	{
		for (vector<cAsteroid*>::iterator iter = theAsteroids.begin(); iter != theAsteroids.end(); ++iter)
		{
			if ((*iter)->collidedWith((*iter)->getBoundingRect(), (*index)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				score = score + 100;
				cout << "Your score is: " && score;
				(*iter)->setActive(false);
 				(*index)->setActive(false);
				
			}
		}
	}

	vector<cBullet*>::iterator index = theRocketBullets.begin();
	while( index != theRocketBullets.end())
	{
		if ((*index)->isActive() == false)
		{
			index = theRocketBullets.erase(index);
		}
		else
		{
			(*index)->update(deltaTime);
			(*index)->render();
			++index;
		}
	}
}

/*
=================================================================
  Sets the velocity for the rocket
=================================================================
*/
void cRocket::setRocketVelocity(glm::vec2 rocketVel)
{
	rocketVelocity = rocketVel;
}
/*
=================================================================
  Gets the rocket velocity
=================================================================
*/
glm::vec2 cRocket::getRocketVelocity()
{
	return rocketVelocity;
}
