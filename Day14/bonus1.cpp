#include <iostream>

class RingBuffer {
    int size = 10;
    char buffer[10];
    int head = 0;
    int tail = 0;

    public:
        void addElement(char value) {
            if (this->tail == this->size) {
                this->tail=0;
                this->head++;
            }

            if ((this->tail - this->head) == -1 && this->tail < this->head) {
                this->head++;
            }

            this->buffer[this->tail] = value;

            this->tail++;
        }
    
        void removeElement() {
            this->buffer[this->head] = 0;
            this->head++;
        }

        void readBuffer() {

            std::cout << "Printing buffer" << std::endl;

            if (this->head == this->tail) {
                std::cout << "Buffer is empty" << std::endl;
                return;
            }

            int currentValue = this->head;

            for ( int i=0; i<this->size; i++) {
                std::cout << this->buffer[currentValue] << std::endl;

                currentValue++;

                if (currentValue == this->size) {
                    currentValue=0;
                }

                if (currentValue == this-> tail) {
                    break;
                }
            }
            
        }
};

int main() {
    RingBuffer ringBuffer;
    ringBuffer.readBuffer();
    ringBuffer.addElement('A');
    ringBuffer.addElement('B');
    ringBuffer.addElement('C');
    ringBuffer.addElement('D');
    ringBuffer.addElement('E');
    ringBuffer.addElement('F');
    ringBuffer.addElement('G');
    ringBuffer.addElement('H');
    ringBuffer.readBuffer();
    ringBuffer.removeElement();
    ringBuffer.readBuffer();
    ringBuffer.addElement('I');
    ringBuffer.addElement('J');
    ringBuffer.addElement('K');
    ringBuffer.addElement('L');
    ringBuffer.readBuffer();

}