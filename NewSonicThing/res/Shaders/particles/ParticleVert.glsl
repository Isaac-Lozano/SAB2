#version 330

in vec2 position;

in mat4 modelViewMatrix;
in vec4 texOffsets;
in float blendFactor;

out vec2 textureCoords1;
out vec2 textureCoords2;
out float blend;

uniform mat4 projectionMatrix;
uniform float numberOfRows;


void main(void)
{
    vec2 textureCoords = position*0.975 + vec2(0.5, 0.5); //position*0.97 + vec2(0.5, 0.5);
    textureCoords.y =  1.0 - textureCoords.y;
    textureCoords /= numberOfRows;
    textureCoords1 = textureCoords + texOffsets.xy;
    textureCoords2 = textureCoords + texOffsets.zw;
    blend = blendFactor;
    
    //vec4 worldPosition = transformationMatrix * vec4(position, 0.0, 1.0);
    //gl_ClipDistance[0] = dot(worldPosition, clipPlane);
    
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 0.0, 1.0);
}
