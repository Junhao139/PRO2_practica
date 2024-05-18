# Río
## 1. leer_rio o lr.
- **ENCARGADO: `River::input_basin()`**
Se leerán los identificadores de las ciudades indicando la estructura de la cuenca. No se escribe nada. Los inventarios de las ciudades quedan vacíos. El barco conserva sus atributos de productos pero no ha realizado viajes en la nueva cuenca.
# Ciudad
## 2. leer_inventario o li.
- **Implementado: `City::`**
Se leerá el identificador de una ciudad.
1. Si la ciudad no existe se escribirá un mensaje de error `error: no existe la ciudad`.
2. Si la ciudad existe, se **leerá un número que indica la cantidad de elementos del inventario y para cada uno de ellos se leerá el identificador del producto, cuantas unidades tiene la ciudad y cuantas necesita.** El número de unidades necesitadas siempre ha de ser mayor que 0.
## 3. leer_inventarios o ls.
- **Implementado: `City::`**
Se leerán los inventarios de ciudades del río, en las mismas condiciones que la funcionalidad anterior. No necesariamente todas las ciudades tendrán inventario.
# Barco
## 4. modificar_barco o mb.
- **Implementado: `Ship::set_all()`**
1. Se leerá el identificador del producto que se quiere comprar y la cantidad, y
2. el identificador del producto que se quiere vender y la cantidad.
3. Si algún producto no existe, se escribirá un mensaje de error.
4. Si los dos productos son el mismo, se escribirá un mensaje de error.
	Se garantiza que ambas cantidades serán no negativas y al menos una de ellas será estrictamente positiva.
# Río y barco
## 5. escribir_barco o eb.
Se escriben los cuatro valores mencionados en la anterior operación y los viajes realizados en la cuenca actual, en orden cronológico. Para cada viaje solo se ha de escribir la última ciudad visitada de la ruta escogida.
# Datos de productos 
- COMPLETO. Encargado: `class ProductData`
## 6. consultar_num o cn.
Escribe cuantos productos diferentes hay.
## 7. agregar_productos o ap.
Se lee el número de productos nuevos, mayor que 0. Sus identificadores serán correlativos a partir del último producto existente. Se leerán sus pesos y volúmenes respectivos.
## 8. escribir_producto o ep.
Se lee el identificador de un producto. Si no existe el producto se escribe un mensaje de error. En caso contrario se escribe el peso y volumen del producto.
# Ciudad
## 9. escribir_ciudad o ec.
Se leerá el identificador de una ciudad. Si la ciudad no existe se escribirá un mensaje de error. Si la ciudad existe, se escribirá su inventario, y el peso y el volumen total de los productos almacenados.
## 10. poner_prod o pp.
1. Se leerá el identificador de una ciudad, de un producto y las unidades que tiene y que quiere.
2. Si el producto no existe escribe un mensaje de error.
3. Si la ciudad no existe, escribe un mensaje de error. 
4. Si el producto ya está en el inventario de la ciudad, escribe un mensaje de error.
5. Si no hay errores, los datos de ese producto se añaden a la ciudad, modificándose el peso y el volumen total si hace falta. Se escribe el peso y el volumen total. El número de unidades necesitadas siempre ha de ser mayor que 0.
## 11. modificar_prod o mp.
1. Se leerá el identificador de una ciudad, de un producto y las unidades que tienen y que quiere.
2. Si el producto no existe escribe un mensaje de error.
3. Si la ciudad no existe, escribe un mensaje de error.
4. Si el producto no está en el inventario de la ciudad, escribe un mensaje de error.
5. Si no hay errores, los datos de ese producto sustituyen a los que había en la ciudad, modificándose el peso y el volumen total si hace falta. Se escribe el peso y el volumen total. El número de unidades necesitadas se puede modificar, pero siempre ha de ser mayor que 0.
## 12. quitar_prod o qp.
1. Se leerá el identificador de una ciudad y de un producto.
2. Si el producto no existe escribe un mensaje de error.
3. Si la ciudad no existe, escribe un mensaje de error.
4. Si el producto no está en el inventario de la ciudad, escribe un mensaje de error.
5. Si no hay errores, se quitan los datos de este producto en la ciudad, modificándose el peso y el volumen total si hace falta. Se escribe el peso y el volumen total.
## 13. consultar_prod o cp.
1. Se leerá el identificador de una ciudad y de un producto.
2. Si el producto no existe escribe un mensaje de error.
3. Si la ciudad no existe, escribe un mensaje de error.
4. Si el producto no está en el inventario de la ciudad, escribe un mensaje de error.
5. Si no hay errores, se escribe cuantas unidades de ese producto tiene y quiere la ciudad.
# Río
## 14. comerciar o co.
Se leerán los identificadores de dos ciudades. Si no existe alguna de las dos (o las dos), se escribe un mensaje de error. Si las ciudades existen y son la misma, se escribe un mensaje de error. Si las ciudades existen y son diferentes, comercian entre ellas.
## 15. redistribuir o re.
No se leen dato#ebs. La ciudad de la desembocadura comercia con su ciudad río arriba a mano derecha y luego con la ciudad río arriba a mano izquierda, y así sucesivamente.
## 16. hacer_viaje o hv.
1. El barco busca la ruta a partir de la desembocadura que le permita comprar y vender el mayor número posible de productos. En caso que haya más de una ruta que lo cumpla, se queda con la más corta, y en caso de que tengan la misma longitud, se queda con la que viene río arriba a mano derecha.
2. Una vez encontrada la ruta, se hace el viaje y se compran y venden los productos a lo largo de la ruta, modificándose los inventarios de las ciudades.
3. Se escribe el total de unidades de productos compradas y vendidas por el barco.
## 17. fin.
Acaba la ejecución.