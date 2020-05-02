import "dart:io";
import "dart:async";
import 'dart:convert';
import "dart:math";
void main(){
    var rut = [1];          //Creamos un arreglo para almacenar cada variable involucrada (rut, nem, resultado en matematica, etc)
    var nem = [1];          //Todos tienen como mimimo un valor, dado que Dart no acepta inicializar arrays que estan "vacios"
    var ranking = [1];
    var prueba_mat = [1];
    var prueba_len = [1];
    var prueba_cien = [1];
    var prueba_hist = [1];
    int superior = 750;         //Esta variable indica el maximo puntaje que puede obtener un estudiante en la psu
    int inferior = 0;           //Despues se explicara porque el puntaje mimino es 0
    int rut_s = 19932391;     //Representa el rut del estudiante con el mayor numero en su registro (se puede modificar)
    int rut_i = 18916641;     //Representa el rut del estudiante con el menor numero en su registro (se puede modificar)
    int contador = 0;          //Para el ciclo while, esta variable representara la condicion de termino
    double resultado;             
    Random random = new Random();  //Variable que se utiliza para obtener numeros aleatorios
    var filename = new File('resulpsu.csv');  //Creamos dos archivos, este con el resultados de las 4 pruebas (mas el ranking y el nem)
    var file = new File('resulest.csv');  //Este archivo va a almacenar los resultados globales del estudiante
    var jj = filename.openWrite(); //Variable para escribir en el archivo 'file.txt' (el de los 6 resultados juntos en un archivo)
    var gg = file.openWrite(); //Variable para escribir en el archivo 'respsu.txt' (el de los resultados finales en un archivo)
    jj.write("Rut" + ";" + "nem" + ";" + "ranking" + ";" + "matematicas" + ";" + "lenguaje" + ";" + "ciencias" + ";" + "historia" + ";" + "\n");
    gg.write("Rut" + ";" + "Resultado_psu" + "\n");
    while (rut_i < rut_s){
      int valor_nem = random.nextInt(superior - inferior); //Valor aleatorio generado en el campo 'nem'
      int valor_ranking = random.nextInt(superior - inferior); //Valor aleatorio generado en el campo 'ranking'
      int valor_mat = random.nextInt(superior - inferior); //Valor aleatorio generado en la prueba de matematica
      int valor_len = random.nextInt(superior - inferior); //Valor aleatorio generado en la prueba de lenguaje
      int valor_cien = random.nextInt(superior - inferior); //Valor aleatorio generado en la prueba de ciencias
      int valor_hist = random.nextInt(superior - inferior); //Valor aleatorio generado en la prueba de historia
      if ((valor_nem > 474) & (valor_ranking > 474) & (valor_mat > 474) & (valor_len > 474) & (valor_cien > 474) & (valor_hist > 474)){
        rut.add(rut_s);  
        nem.add(valor_nem);    //Si se cumplen todas las condiciones a la vez, el registro queda guardado en sus respectivos arrays
        ranking.add(valor_ranking);
        prueba_mat.add(valor_mat);
        prueba_len.add(valor_len);
        prueba_cien.add(valor_cien);
        prueba_hist.add(valor_hist);
        contador++;
        rut_i++;
      }
    }
    int pp = contador + 1; //Aumentamos en 1 la cantidad del contador para realizar las iteraciones de forma adecuada a cada array

    for(int u = 1; u < pp; u++){
      String s_rut = rut[u].toString(); //Convertimos el rut a una cadena de caracteres
      String s_nem = nem[u].toString(); //Convertimos el mem a una cadena de caracteres
      String s_ranking = ranking[u].toString(); //Convertimos el ranking a una cadena de caracteres
      String s_mat = prueba_mat[u].toString(); //Convertimos el resultado en matematicas a una cadena de caracteres
      String s_len = prueba_len[u].toString(); //Convertimos el resultado en lenguaje a una cadena de caracteres
      String s_cien = prueba_cien[u].toString(); //Convertimos el resultado en ciencias a una cadena de caracteres
      String s_hist = prueba_hist[u].toString(); //Convertimos el resultado en historia a una cadena de caracteres
      var palabra = s_rut + ";" + s_nem + ";" + s_ranking + ";" + s_mat + ";" + s_len + ";" + s_cien + ";" + s_hist + ";" + "\n";
      jj.write(palabra); //La variable palabra contiene el formato solicitado para escribir cada uno de los resultados en un archivo
    }
    jj.close();
    for (int o = 1; o < pp; o++){

      if(prueba_cien[o] > prueba_hist[o]){ //Si el estudiante obtuvo mejor puntaje en ciencias que en historia...
        resultado = (nem[o] * 0.1) + (ranking[o] * 0.25) + (prueba_mat[o] * 0.35) + (prueba_len[o] * 0.2) + (prueba_cien[o] * 0.1);
        String s_resultado = resultado.toString(); //El resultado en ciencias es el que se toma en cuenta para realizar el calculo
        String s_rut = rut[o].toString();
        var resul_est = s_rut + ";" + s_resultado;
        gg.write(resul_est);
        gg.write("\n");
      }

      if(prueba_cien[o] < prueba_hist[o]){ //Si el estudiante obtuvo peor puntaje en ciencias que en historia...
        resultado = (nem[o] * 0.1) + (ranking[o] * 0.25) + (prueba_mat[o] * 0.35) + (prueba_len[o] * 0.2) + (prueba_hist[o] * 0.1);
        String s_resultado = resultado.toString(); //El resultado en historia es el que se toma en cuenta para realizar el calculo
        String s_rut = rut[o].toString();
        var resul_est = s_rut + ";" + s_resultado;
        gg.write(resul_est);
        gg.write("\n");
      }

      if(prueba_cien[o] == prueba_hist[o]){ //Si el estudiante obtuvo el mismo puntaje en ciencias y en historia...
        resultado = (nem[o] * 0.1) + (ranking[o] * 0.25) + (prueba_mat[o] * 0.35) + (prueba_len[o] * 0.2) + (prueba_cien[o] * 0.1);
        String s_resultado = resultado.toString(); //Entonces se elige cualquiera de los dos resultados (en este caso, el de ciencias)
        String s_rut = rut[o].toString();
        var resul_est = s_rut + ";" + s_resultado;
        gg.write(resul_est);
        gg.write("\n");
      }
      
    }
    gg.close();
}
