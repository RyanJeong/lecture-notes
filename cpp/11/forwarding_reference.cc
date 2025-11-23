#ifdef CPP_11_NOBUILD
template <typename T>
void ForwardingReference(T&& param) {
  // param is a forwarding reference (universal reference)
  // It can bind to both lvalues and rvalues.
}
#endif
