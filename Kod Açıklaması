# Veri-Yapilari-2.-Kisa-Sinav-2.-odev

Bırch Algoritması Örneğinin Çalışma Prensibi 

Bu C kodu, BIRCH (Balanced Iterative Reducing and Clustering using Hierarchies) algoritmasını uygulayan bir örnektir. Aşağıda kodun nasıl çalıştığına dair ayrıntılı bir açıklama bulunmaktadır:

İlk olarak, DataPoint adında bir yapı tanımlanır. Bu yapı, veri noktalarının özellik vektörünü (features) ve küme kimliğini (clusterID) içerir.

calculateDistance fonksiyonu, iki veri noktası arasındaki Öklidyen mesafesini hesaplar. İki DataPoint yapısını ve özellik sayısını alır ve mesafeyi döndürür.

birchAlgorithm fonksiyonu, BIRCH algoritmasının uygulandığı ana fonksiyondur. İki aşamada gerçekleştirilir:

a.) Birinci aşama: Veri noktaları çekirdek ağaçlarına eklenir veya yeni bir çekirdek ağacı oluşturulur. Bu aşamada, her veri noktası üzerinde döngü oluşturulur. Her veri noktası, mevcut çekirdek ağaçlarıyla karşılaştırılır ve bir çekirdek ağacının yarıçapı içinde bir çekirdek nokta bulunamazsa yeni bir çekirdek ağacı oluşturulur.

b.) İkinci aşama: Veri noktaları çekirdek ağaçlarına eklenir veya mevcut çekirdek ağaçlarına birleştirilir. Bu aşamada, her veri noktası üzerinde döngü oluşturulur. Her veri noktası, mevcut çekirdek ağaçlarıyla karşılaştırılır ve en yakın çekirdek ağaca eklenir. Eğer en yakın çekirdek ağaç yoksa, yeni bir çekirdek ağacı oluşturulur.
Bu aşamalar sonunda, her çekirdek ağacının kimlikleri ve içerdikleri veri noktalarının sayıları hesaplanır ve ekrana yazdırılır.

main fonksiyonunda, örnek veri noktaları oluşturulur. İlgili değişkenler tanımlanır ve birchAlgorithm fonksiyonu çağrılır. Sonuç olarak, kümeleme sonuçları ekrana yazdırılır.

Kod ayrıca, bellek yönetimi için gerekli olan malloc ve free işlemlerini içerir. Örnek veri noktaları oluşturulurken, her veri noktası için dinamik olarak bellek ayrılır ve ardından bellek temizlenir. Bu, bellek sızıntısını önlemek için önemlidir.

Algoritmanın çalışma mantığı, veri noktalarını çekirdek ağaçlarıyla gruplandırarak ve çekirdek ağaçlarını birleştirerek kümeleme işlemini gerçekleştirmektir.
