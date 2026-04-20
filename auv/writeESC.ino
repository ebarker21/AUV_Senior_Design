// Write to ESC
void writeESC(int index, int value) {
  esc[index].writeMicroseconds(value);
}