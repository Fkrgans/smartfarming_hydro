# Business Requirements Document (BRD)

## 1. Informasi Dokumen

| Item | Keterangan |
|---|---|
| Nama proyek | SmartHydro |
| Jenis proyek | Sistem IoT monitoring dan kontrol hidroponik |
| Status saat ini | Web dashboard dan demo live telah tersedia; pengembangan notifikasi Telegram menjadi fase berikutnya |
| Pemilik proyek | Tim SmartHydro |
| Versi dokumen | 1.0 |
| Tanggal | 20 September 2026 |

## 2. Ringkasan Eksekutif (Executive Summary)

Budidaya hidroponik membutuhkan pemantauan kondisi air dan lingkungan secara berkala. Pengukuran pH, konsentrasi nutrisi, suhu, dan kelembapan secara manual dapat menyebabkan keterlambatan dalam mengetahui perubahan kondisi tanaman. Keterlambatan tersebut dapat menurunkan kualitas pertumbuhan tanaman dan meningkatkan risiko kerusakan sistem.

SmartHydro diusulkan sebagai sistem IoT untuk mengumpulkan data sensor hidroponik dan menampilkannya dalam dashboard web secara real-time. Sistem yang telah dikerjakan mencakup halaman web, dashboard monitoring, visualisasi data, penerimaan data sensor melalui backend, komunikasi real-time, serta kontrol relay/perangkat keras.

Dashboard saat ini dapat digunakan sebagai demo live pada `/dashboard?demo=1`. Untuk pengembangan berikutnya, sistem akan ditingkatkan menjadi aplikasi monitoring operasional yang dapat mengirim informasi dan peringatan ke Telegram ketika nilai sensor berada di luar batas normal, termasuk notifikasi untuk kondisi perangkat dan ringkasan monitoring.

## 3. Tujuan Proyek (Project Objectives)

### 3.1 Tujuan utama

Menyediakan satu sistem monitoring hidroponik yang membantu pengguna melihat kondisi instalasi secara cepat, mengambil tindakan berdasarkan data, dan menerima peringatan tanpa harus selalu membuka dashboard.

### 3.2 Target yang dapat diukur

1. Menampilkan data pH, PPM, suhu, dan kelembapan terbaru pada dashboard tanpa refresh halaman.
2. Meneruskan data dari perangkat ke dashboard dengan target latensi kurang dari 1 detik setelah data diterima server.
3. Mendukung pengiriman data sensor secara berkala, dengan interval perangkat yang saat ini dirancang sekitar 5 detik.
4. Mengirim notifikasi Telegram ketika nilai sensor melewati ambang batas yang telah dikonfigurasi.
5. Mengurangi ketergantungan pada pemeriksaan manual dengan menyediakan akses informasi melalui Telegram.
6. Menyediakan kontrol relay dari dashboard dan meneruskan perintah ke perangkat melalui backend/MQTT pada fase operasional.
7. Memastikan sistem dapat digunakan melalui desktop dan perangkat mobile pada jaringan yang sama.

## 4. Ruang Lingkup (Project Scope)

### 4.1 In-scope: sudah dikerjakan

- Halaman landing page dan informasi produk.
- Login dan pendaftaran pengguna dasar.
- Dashboard web responsif untuk monitoring hidroponik.
- Tampilan metrik pH, PPM, suhu, dan kelembapan.
- Grafik tren data sensor.
- Status koneksi dan status kesehatan sistem.
- Pembaruan data menggunakan Socket.io tanpa refresh halaman.
- Mode demo dashboard dengan data simulasi untuk kebutuhan presentasi.
- Endpoint backend untuk menerima data sensor melalui `POST /api/sensor`.
- Endpoint untuk membaca data sensor terbaru melalui `GET /api/sensor/latest`.
- Kontrol relay dari dashboard/backend.
- Dukungan komunikasi MQTT untuk data sensor dan perintah relay.
- Firmware ESP32/NodeMCU dan contoh firmware ESP8266 untuk pengiriman data/perangkat.
- Penyimpanan data terbaru secara sementara di memori server.
- Pengiriman alert Telegram dasar ketika nilai sensor berada di luar ambang batas, jika kredensial Telegram sudah dikonfigurasi.

### 4.2 In-scope: rencana pengembangan berikutnya

- Aplikasi monitoring yang dapat diakses dari perangkat mobile.
- Integrasi Telegram Bot untuk notifikasi otomatis.
- Notifikasi kondisi pH, PPM, suhu, kelembapan, dan kemungkinan perangkat tidak terhubung.
- Pesan uji Telegram untuk memastikan konfigurasi bot berjalan.
- Konfigurasi ambang batas dan interval cooldown notifikasi.
- Ringkasan kondisi kebun atau instalasi berdasarkan data terbaru.
- Pencatatan histori notifikasi dan histori data sensor secara persisten.
- Pengujian integrasi antara sensor, backend, MQTT, dashboard, dan Telegram.

### 4.3 Out-of-scope

- Perancangan atau produksi instalasi hidroponik fisik dan struktur kebun.
- Penjualan hasil panen, manajemen stok, akuntansi, dan marketplace.
- Diagnosis penyakit tanaman berbasis kamera atau kecerdasan buatan.
- Otomasi penuh dosis nutrisi tanpa validasi manusia dan kalibrasi sensor.
- Dukungan semua jenis sensor atau mikrokontroler di luar perangkat yang disepakati.
- Aplikasi native Android/iOS khusus; fase awal menggunakan web responsif dan Telegram.
- Jaminan bahwa data demo mewakili kondisi sensor produksi.
- Penggunaan data in-memory sebagai histori produksi jangka panjang.

## 5. Daftar Pemangku Kepentingan (Stakeholders)

| Pemangku kepentingan | Peran dan tanggung jawab |
|---|---|
| Pemilik/sponsor proyek | Menetapkan tujuan, prioritas, anggaran, dan menyetujui hasil akhir. |
| Pengelola hidroponik | Menggunakan dashboard dan Telegram, memeriksa kondisi tanaman, serta menindaklanjuti peringatan. |
| Admin sistem | Mengelola akses pengguna, konfigurasi sistem, ambang batas, dan kredensial integrasi. |
| Tim pengembang | Membangun frontend, backend, API, integrasi MQTT, dan integrasi Telegram. |
| Teknisi IoT/hardware | Memasang, mengkalibrasi, memelihara sensor, mikrokontroler, relay, dan koneksi jaringan. |
| Penguji/validator | Memastikan data, notifikasi, kontrol relay, dan tampilan dashboard sesuai kebutuhan. |
| Penyedia layanan eksternal | Menyediakan jaringan Wi-Fi, broker MQTT, hosting backend, dan Telegram Bot API. |
| Pengguna akhir | Menerima informasi kondisi sistem dan mengambil tindakan sesuai prosedur operasional. |

## 6. Kebutuhan Bisnis (Business Requirements)

| ID | Kebutuhan |
|---|---|
| BR-01 | Pengguna harus dapat melihat nilai terbaru pH, PPM, suhu, dan kelembapan dari satu dashboard. |
| BR-02 | Dashboard harus memperbarui data tanpa pengguna memuat ulang halaman. |
| BR-03 | Pengguna harus dapat melihat kecenderungan perubahan nilai melalui grafik. |
| BR-04 | Sistem harus memberikan indikator apakah data sensor dan koneksi server tersedia. |
| BR-05 | Admin atau pengguna berwenang harus dapat mengubah status perangkat/relay melalui antarmuka yang tersedia. |
| BR-06 | Sistem harus menerima data dari perangkat IoT dengan format yang konsisten dan menolak data wajib yang tidak lengkap. |
| BR-07 | Sistem harus membedakan mode demo dan mode operasional agar data simulasi tidak dianggap sebagai data produksi. |
| BR-08 | Sistem harus memberi penanda kondisi normal atau di luar batas untuk setiap parameter sensor. |
| BR-09 | Sistem harus mengirim notifikasi Telegram jika satu atau lebih parameter melewati batas yang dikonfigurasi. |
| BR-10 | Notifikasi harus memiliki waktu kejadian, parameter yang bermasalah, nilai aktual, dan rentang ideal. |
| BR-11 | Sistem harus mencegah pengiriman notifikasi berulang dalam waktu singkat melalui cooldown. |
| BR-12 | Admin harus dapat menguji koneksi Telegram tanpa menunggu alarm sensor terjadi. |
| BR-13 | Sistem harus tetap menampilkan data terakhir dan status koneksi ketika perangkat sementara tidak mengirim data. |
| BR-14 | Informasi sensitif seperti token bot Telegram tidak boleh ditampilkan pada dashboard atau dikirim ke log pengguna. |
| BR-15 | Sistem harus menyediakan dokumentasi konfigurasi sensor, MQTT, backend, dan Telegram untuk proses operasional.

## 7. Alur Bisnis Utama

1. Sensor pada ESP32/NodeMCU membaca kondisi instalasi hidroponik.
2. Perangkat mengirim data ke backend secara berkala melalui HTTP atau MQTT.
3. Backend memvalidasi data, menyimpan nilai terbaru, dan meneruskannya ke dashboard secara real-time.
4. Dashboard memperbarui kartu metrik, grafik, status, dan histori sementara.
5. Backend membandingkan data dengan ambang batas yang telah ditentukan.
6. Jika terjadi kondisi di luar batas dan cooldown telah berakhir, backend mengirim pesan melalui Telegram Bot API.
7. Pengguna memeriksa dashboard atau Telegram lalu melakukan tindakan yang diperlukan, termasuk mengendalikan relay bila tersedia.

## 8. Asumsi, Ketergantungan, dan Batasan

### 8.1 Asumsi

- Sensor telah terpasang dengan benar dan dikalibrasi sesuai jenis instalasi.
- Perangkat IoT memiliki daya listrik dan koneksi Wi-Fi yang stabil.
- Nilai ambang batas disepakati oleh pengelola berdasarkan jenis tanaman dan metode budidaya.
- Pengguna memiliki akun Telegram dan telah memulai percakapan dengan bot.
- Pengguna memahami bahwa notifikasi adalah alat bantu keputusan, bukan pengganti pemeriksaan fisik.
- Data demo hanya digunakan untuk presentasi tampilan dan alur aplikasi.

### 8.2 Ketergantungan

- Node.js dan dependency backend tersedia pada lingkungan server.
- Jaringan Wi-Fi tersedia untuk perangkat IoT.
- Broker MQTT tersedia jika mode MQTT digunakan.
- Telegram Bot API dapat diakses dari server.
- Token bot dan chat ID Telegram dikonfigurasi melalui environment variable.
- Hosting atau server backend berjalan terus selama monitoring operasional dibutuhkan.
- Library frontend, Socket.io, Chart.js, dan layanan CDN yang digunakan dapat dimuat.

### 8.3 Batasan

- Data sensor terbaru saat ini disimpan di memori server dan dapat hilang ketika server dimulai ulang.
- Mode demo menggunakan data simulasi dan tidak mengendalikan perangkat produksi.
- Akurasi hasil bergantung pada kualitas, pemasangan, dan kalibrasi sensor.
- Telegram bergantung pada koneksi internet dan ketersediaan Telegram Bot API.
- Cooldown notifikasi dapat menyebabkan alarm berulang tidak dikirim selama periode tertentu.
- Kredensial contoh pada lingkungan pengembangan tidak boleh digunakan untuk produksi.
- Fitur multi-kebun, multi-perangkat, dan hak akses rinci belum menjadi bagian dari fase awal.

## 9. Kebutuhan Non-Fungsional (Non-Functional Requirements)

### 9.1 Kinerja

- Target respons API pembacaan data terbaru kurang dari 100 ms pada jaringan lokal yang normal.
- Target pembaruan dashboard kurang dari 1 detik setelah backend menerima data.
- Sistem harus mendukung beberapa klien dashboard secara bersamaan untuk kebutuhan operasional awal.
- Sistem harus menggunakan cooldown atau mekanisme sejenis agar lonjakan data tidak membanjiri Telegram.

### 9.2 Ketersediaan dan keandalan

- Kegagalan Telegram tidak boleh menghentikan penerimaan data sensor dan pembaruan dashboard.
- Koneksi MQTT yang terputus harus dapat tersambung kembali secara otomatis jika layanan tersedia.
- Sistem harus mencatat kegagalan integrasi agar dapat ditelusuri oleh admin.
- Status koneksi perangkat dan backend harus dapat diketahui pengguna.

### 9.3 Keamanan

- Token bot, chat ID, kredensial MQTT, dan konfigurasi sensitif disimpan di environment variable.
- Endpoint kontrol perangkat perlu dilindungi autentikasi dan otorisasi sebelum digunakan di produksi.
- Akses produksi harus menggunakan HTTPS atau jaringan yang terlindungi.
- Input dari perangkat dan pengguna harus divalidasi sebelum diproses.
- Pesan Telegram tidak boleh memuat rahasia sistem.

### 9.4 Usability dan kompatibilitas

- Dashboard harus dapat digunakan pada desktop dan layar mobile.
- Label sensor, satuan, rentang ideal, dan waktu pembaruan harus mudah dipahami.
- Perbedaan mode demo dan mode live harus terlihat jelas.
- Bahasa utama antarmuka dan notifikasi adalah Bahasa Indonesia.

## 10. Jadwal dan Lini Masa (Timeline & Milestones)

| Fase | Perkiraan durasi | Milestone | Hasil |
|---|---:|---|---|
| Fase 1 | Selesai | Web dan dashboard demo | Landing page, login dasar, dashboard, grafik, dan kontrol tersedia. |
| Fase 2 | Selesai/sebagian | Backend dan koneksi IoT | API sensor, Socket.io, relay, MQTT, dan firmware dasar tersedia. |
| Fase 3 | 1-2 minggu | Telegram MVP | Bot terhubung, pesan uji berhasil, dan alert ambang batas terkirim. |
| Fase 4 | 1-2 minggu | Monitoring operasional | Pengaturan ambang batas, cooldown, status perangkat, dan dokumentasi operasional selesai. |
| Fase 5 | 1-2 minggu | Persistensi dan pengujian | Histori data/notifikasi, pengujian integrasi, dan perbaikan keamanan awal selesai. |
| Fase 6 | 1 minggu | Pilot dan peluncuran | Uji pada instalasi nyata, pelatihan pengguna, evaluasi, dan rilis awal. |

Jadwal dapat disesuaikan berdasarkan ketersediaan hardware, kestabilan jaringan, kebutuhan penyimpanan data, dan hasil uji lapangan.

## 11. Kriteria Penerimaan (Acceptance Criteria)

### 11.1 Dashboard dan data sensor

- Pengguna dapat membuka dashboard pada desktop dan mobile.
- Dashboard menampilkan pH, PPM, suhu, dan kelembapan dengan satuan yang benar.
- Data baru dari endpoint sensor muncul pada dashboard tanpa refresh halaman.
- Grafik menampilkan perubahan data dan tidak membuat halaman gagal ketika data belum tersedia.
- Mode demo dapat dijalankan melalui `/dashboard?demo=1` dan diberi penanda sebagai demo.

### 11.2 Kontrol dan integrasi perangkat

- Data dengan field wajib yang hilang ditolak dengan respons error yang dapat dipahami.
- Perubahan status relay menghasilkan respons API dan event ke klien yang terhubung.
- Jika MQTT aktif, perintah relay diterbitkan ke topic yang dikonfigurasi.
- Putusnya MQTT tidak menghentikan fungsi dashboard dan API dasar.

### 11.3 Telegram

- Pesan uji dapat dikirim setelah `TELEGRAM_BOT_TOKEN` dan `TELEGRAM_CHAT_ID` dikonfigurasi.
- Nilai di luar batas menghasilkan pesan Telegram yang memuat nama parameter, nilai aktual, rentang ideal, dan waktu kejadian.
- Nilai normal tidak mengirim alert abnormal.
- Alert yang sama tidak dikirim berulang sebelum cooldown berakhir.
- Kegagalan Telegram dicatat dan tidak menghentikan proses penerimaan data sensor.
- Token bot tidak muncul pada respons API, antarmuka, atau pesan notifikasi.

### 11.4 Persetujuan akhir

Proyek dinyatakan siap untuk pilot apabila seluruh kriteria di atas lulus dalam pengujian lokal dan minimal satu pengujian dengan perangkat sensor nyata. Peluncuran produksi memerlukan persetujuan pemilik proyek, konfigurasi keamanan, backup konfigurasi, serta prosedur penanganan ketika sensor, jaringan, server, atau Telegram tidak tersedia.

## 12. Risiko dan Mitigasi Awal

| Risiko | Dampak | Mitigasi |
|---|---|---|
| Sensor tidak terkalibrasi | Data menyesatkan dan alarm salah | Kalibrasi berkala, validasi nilai, dan pemeriksaan fisik. |
| Wi-Fi atau broker MQTT terputus | Data tidak masuk ke dashboard | Tampilkan status koneksi, reconnect otomatis, dan sediakan pemeriksaan manual. |
| Telegram API tidak tersedia | Pengguna terlambat menerima peringatan | Dashboard tetap menjadi sumber utama, log error, dan lakukan retry terbatas. |
| Alert terlalu sering | Pengguna mengabaikan notifikasi | Terapkan cooldown, ambang batas yang disepakati, dan ringkasan alert. |
| Server restart | Histori in-memory hilang | Gunakan database pada fase persistensi dan siapkan backup. |
| Akses kontrol tidak terlindungi | Relay dapat diubah oleh pihak tidak berwenang | Wajibkan autentikasi, otorisasi, dan HTTPS sebelum produksi. |
