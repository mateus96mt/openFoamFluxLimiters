# Instruções

## 1. Instalação do OpenFoam em sua máquina:

Para utilizar esse repositório é necessário instalar o OpenFoam na sua máquina (Linux).

A instalação em sistemas ubuntu pode ser feita seguindo este tutorial: [instalação ubuntu]: https://openfoam.org/download/8-ubuntu/

Instalações em outras versões Linux pode ser feita através desse tutorial: [instalação]: https://openfoam.org/download/

Com o OpenFoam devidamente instalado em sua máquina de acordo com os tutoriais acima podemos avançar para instalação dos esquemas Upwind deste repositório (TOPUS, FSFL, SDPUS-C1 e EPUS)

## 2. Instalação dos esquemas TOPUS, FSFL, SDPUS-C1 e EPUS no OpenFoam:

### 2.1 Copiar os arquivos necessários deste repositório para o local de instalação do OpenFoam em sua máquina.

Navegue pelo local de instalação do OpenFoam em sua máquina até o caminho abaixo:

Copie as pastas desse repositório em 'openFoamFluxLimiters/src/finiteVolume/interpolation/surfaceInterpolation/limitedSchemes/' para o mesmo caminho no local de instalação do OpenFoam em sua máquina '/opt/openfoam8/src/finiteVolume/interpolation/surfaceInterpolation/limitedSchemes'.

Talves seja necessário permissão de administrador para copiar os arquivos, se atende a isto.

Note que o caminho '/opt/openfoam8/...' pode ser diferente em sua máquina se o OpenFoam for instalado por outros meios que não os citados neste tutorial.

### 2.2 Incluir os arquivos copiados anteriormente no arquivo de compilação do OpenFoam

Navegue até '/opt/openfoam8/src/finiteVolume/Make/' no diretório do OpenFoam em sua máquina

Abra o arquivo 'file' e adicione o seguinte trecho de código no mesmo:

```c++
$(limitedSchemes)/TOPUS/TOPUS.C
$(limitedSchemes)/FSFL/FSFL.C
$(limitedSchemes)/SD_PUS_C1/SD_PUS_C1.C
$(limitedSchemes)/EPUS/EPUS.C
```

esse trecho de código deve ser inserido na definição da variável ```limitedSchemes```, ficando como abaixo:

```c
limitedSchemes = $(surfaceInterpolation)/limitedSchemes
$(limitedSchemes)/limitedSurfaceInterpolationScheme/limitedSurfaceInterpolationSchemes.C
$(limitedSchemes)/upwind/upwind.C
$(limitedSchemes)/blended/blended.C
$(limitedSchemes)/Gamma/Gamma.C
$(limitedSchemes)/SFCD/SFCD.C
$(limitedSchemes)/Minmod/Minmod.C
$(limitedSchemes)/vanLeer/vanLeer.C
$(limitedSchemes)/vanAlbada/vanAlbada.C
$(limitedSchemes)/TOPUS/TOPUS.C
$(limitedSchemes)/FSFL/FSFL.C
$(limitedSchemes)/SD_PUS_C1/SD_PUS_C1.C
$(limitedSchemes)/EPUS/EPUS.C
```

### 2.3 Compilar o OpenFoam para incluir os novos limitadores de fluxo

Navegue até o local de instalação do OpenFoam em sua máquina '/opt/openfoam8/src/finiteVolume' e abra um terminal dentro desta pasta

Com o terminal aberto execute os seguintes comandos:

```
wmake
```

O processo de compilação deve começar

Caso ocorra algum erro de permissão digite o comando 

```
sudo -i
cd /opt/openfoam8/src/finiteVolume
```

Novamente reforço que o caminho pode ser diferente dependendo da versão do OpenFoam em sua máquina, por exemplo a versão 9 teria o caminho '/opt/openfoam9...'

Se o processo de compilação tiver ocorrido sem erros a compilação foi um sucesso!
