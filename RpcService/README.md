### RpcService

Пример демонстирует класс для приема и отправки сообщений.
Позволяет не меняя сам класс RpcService, передавать и получать 
экземпляры любых  типов (со вложенными свойствами)   

Используемые технологии:
* typelists  c помощью boost::hana
* интроспекция с помощью QMetaObject
