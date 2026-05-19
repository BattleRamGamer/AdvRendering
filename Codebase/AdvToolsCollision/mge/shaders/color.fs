//DIFFUSE COLOR FRAGMENT SHADER
// #version 330 // for glsl version (12 is for older versions , say opengl 2.1
// uniform vec3 diffuseColor;
// out vec4 fragment_color;
// void main( void ) {
// 	fragment_color = vec4 (diffuseColor,1);
// }
//DIFFUSE COLOR FRAGMENT SHADER
#version 400

uniform vec4 diffuseColor;
out vec4 fragment_color;

in vec2 vuv;

void main( void ) {
	
	if (vuv.x >= 0.5) {
		if (vuv.y >= 0.5) {
			// Top right
			// (A) Grid Nr (a)
			if (diffuseColor.a <= 0.15f) fragment_color = vec4(1, 0, 0, 1);
			else if (diffuseColor.a <= 0.25f) fragment_color = vec4(0, 1, 0, 1);
			else if (diffuseColor.a <= 0.35f) fragment_color = vec4(0, 0, 1, 1);
			else fragment_color = vec4(1, 1, 1, 1);
		}
		else {
			// Bottom right
			// (B) Cell Y (b)
			fragment_color = vec4(diffuseColor.b, 1-diffuseColor.b, 0, 1);
		}
	}
	else {
		if (vuv.y >= 0.5) {
			// Top left (r)
			// (R) Is Colliding? (r)
			if (diffuseColor.r == 0) fragment_color = vec4(1, 0, 0, 1);
			if (diffuseColor.r == 1) fragment_color = vec4(0, 1, 0, 1);
		}
		else {
			// Bottom left
			// (G) Cell X (g)
			fragment_color = vec4(diffuseColor.g, 1-diffuseColor.g, 0, 1);
		}
}

//	if(vuv.y < 0.5){
//fragment_color = diffuseColor;
//	} else {
//fragment_color = vec4 (diffuseColor.r, vuv.x,vuv.y,1);
//
//}
	
}
