extern int g_offset;  // defined in another module, may be interposed
__attribute__((visibility("hidden"))) int g_scale = 10;  // library-internal
int ReadRaw(int channel);  // external function

int ReadScaled(int channel) { return ReadRaw(channel) * g_scale + g_offset; }
