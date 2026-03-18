/// <reference types="vite/client" />

// Declare .vue files as valid modules so TypeScript resolves their imports.
declare module "*.vue" {
  import type { DefineComponent } from "vue"
  const component: DefineComponent<
    Record<string, unknown>,
    Record<string, unknown>,
    unknown
  >
  export default component
}
