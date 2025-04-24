//
// Created by tanhao on 2025/4/24.
//

#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H


namespace Hazel{

    class GraphicsContext
    {
    public:
       virtual void Init()        =0 ;
       virtual void SwapBuffers() =0 ;

    };



}


#endif //GRAPHICSCONTEXT_H
