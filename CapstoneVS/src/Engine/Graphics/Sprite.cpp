#include "Sprite.h"

Sprite::Sprite() {
        xPos = 0;
        yPos = 0;
        texture = Texture();
}

Sprite::Sprite(string imagePath) {
        texture = Texture(imagePath);
        xPos = 0;
        yPos = 0;
}

Sprite::Sprite(string imagePath, float _xPos, float _yPos) {
        texture = Texture(imagePath);
        xPos = _xPos;
        yPos = _yPos;
}

void Sprite::update() {

}

void Sprite::render() {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture.getId());
        glLoadIdentity();

        //translations -> rotations -> scaling
        glTranslatef(xPos, yPos, 0);
        //glRotatef
        //glScalef
        
        //Rendering
        glColor4f(1, 1, 1, 1);
        glBegin(GL_QUADS);
        //WARNING for images 0, 0 is bottom left
        glTexCoord2f(0, 0);
        glVertex2f(0, 0);

        glTexCoord2f(1, 0);
        glVertex2f( texture.getWidth(), 0);

        glTexCoord2f(1, 1);
        glVertex2f(texture.getWidth(), texture.getHeight());
        
        glTexCoord2f(0, 1);
        glVertex2f(xPos,texture.getHeight());
        
        glEnd();

        glDisable(GL_TEXTURE_2D);
}