CXX=g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
OBJECTS= graphicDisplay.o xWindow.o BlockO.o Blind.o Block.o BlockI.o BlockJ.o BlockL.o BlockS.o BlockT.o BlockZ.o Board.o Cell.o cmdProcessor.o DoNothing.o Force.o Heavy.o main.o newBlock.o Position.o Score.o seDecorator.o SpecialEffect.o TextDisplay.o BlockExtra.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=biquadris -lX11

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean
