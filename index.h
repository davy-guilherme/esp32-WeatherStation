#ifndef INDEX_H // diretiva de pré-processador que verifica se o símbolo INDEX_H não foi definido anteriormente. Essa verificação é usada para evitar a inclusão duplicada do arquivo de cabeçalho
#define INDEX_H

// R"===== é usado para definir uma string de múltiplas linhas (raw string literal) que permite a quebra de linha e preserva os espaços em branco.

// %TEMPERATURE%: Este é um marcador de posição que você pode usar para representar a temperatura. Você pode substituir esse marcador pelo valor real da temperatura quando você enviar a resposta.

const char* html_content = R"=====(
<html>
  <body>
    <h1>Temperatura:</h1>
    <p id='temperatura'>
      %TEMPERATURE% &#8451;
    </p>
    <script>
      setInterval(function() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById('temperatura').innerHTML = this.responseText;
          }
        };
        xhttp.open('GET', '/get-temperatura', true);
        xhttp.send();
      }, 5000);
    </script>
  </body>
</html>
)=====";

#endif
