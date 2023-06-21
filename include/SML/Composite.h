#ifndef SML_COMPOSITE_H
#define SML_COMPOSITE_H

#include <memory>

class Composite {
public:
    virtual ~Composite() {}

    // 添加一个子节点
    virtual void AddChild(std::shared_ptr<Composite> child) = 0;

    // 移除一个子节点
    virtual void RemoveChild(std::shared_ptr<Composite> child) = 0;

    // 获取子节点数量
    virtual int GetChildCount() const = 0;

    // 获取指定索引的子节点
    virtual std::shared_ptr<Composite> GetChild(int index) const = 0;

    // 渲染函数
    virtual void Render() const = 0;
};

#endif // SML_COMPOSITE_H