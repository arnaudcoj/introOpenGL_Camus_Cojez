Camus Tristan
Cojez Arnaud

Nous n'avons pas rencontré de problèmes et avons fini le tp.
Pour les questions qui ne sont pas dans le README, se référer au code.

Les snapshots sont disponibles dans le dossier snapshot et sont nommés en fonction des questions correspondantes.

______

Q8.
Les VBO sont des buffers qui contiennent les informations brutes, VAO permet d'associer les valeurs du VBO aux attributs du shader.
Le program shader se sert des informations données plus haut afin de construire une image.

Q9.
Sommets correspondant aux triangles :
 2  3 4
0 1  5

Q11.
Les varying sont des valeurs que l'on peut passer au vertex à l'aide des VAO/VBO, qui peuvent être modifiées et échangées entre vertex shader et fragment shader.

Q12.
OpenGL place les sommets 3 par 3 et affiche les triangles associés. Vu que l'on a modifié la position des sommets, ils ne sont pas traités dans le même ordre, donc les triangles sont différents.

Q13.
0 3 2  5 1 4

Q15.
Les couleurs ne sont pas les mêmes car les couleurs sont dans le même ordre qu'au départ alors que l'ordre des sommets a été modifié. Les sommets ont donc été associés à d'autres couleurs. Le fait de tracer par element ne modifie pas cette association.

Q16.
Les deux triangles ont un sommet commun et donc une couleur commune car on utilise, grâce aux élements, les mêmes attributs.

Q21.
Il ne faut pas modifier la copie des VBO, ni l'init des VAO, ni le program shader. Cependant il faut prendre en compte la taille du tableau de positions dans glDrawArrays ( _trianglePosition.size()/3 )

Q26.
- On dit à OpenGL que l'on va utiliser la texture 0 avec :
  glActiveTexture(GL_TEXTURE0);
- On associe l'unité de texture 0 déclarée plus haut à la texture lagoon.jpg chargée précedemment avec :
  glBindTexture(GL_TEXTURE_2D,_textureId);
- On donne au shader l'unité de texture :
  glUniform1f(glGetUniformLocation(_shader0,"texture"),0);
- On dessine avec :
  glDrawArrays(GL_TRIANGLE_STRIP,0,_trianglePosition.size()/3);
